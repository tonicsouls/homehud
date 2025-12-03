/*
  Backup: src/main.cpp
  Timestamp: 2025-12-01T00:00:00
  Notes: Save point before changes / flashing
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// E-Ink Display Pins for ESP32-S3
#define EPD_CS     10
#define EPD_DC     11
#define EPD_RST    12
#define EPD_BUSY   13

// Use the 7.5-inch black/white display
GxEPD2_BW<GxEPD2_750_T7, GxEPD2_750_T7::HEIGHT> display(GxEPD2_750_T7(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

// --- WiFi & API Configuration ---
const char* ssid = "Omni.here"; // <-- IMPORTANT: REPLACE WITH YOUR WIFI NAME
const char* password = "8176761765"; // <-- IMPORTANT: REPLACE WITH YOUR WIFI PASSWORD
const String api_url = "https://script.google.com/macros/s/AKfycbztMUdiwwnV4cJOIx6hk-FE8zhdbthOoI6a73tQ1C35NySe-_NRNXkuSdNyD7Lzjt7W9g/exec";

// --- Deep Sleep Configuration ---
#define uS_TO_S_FACTOR 1000000ULL  // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP  1800       // Time ESP32 will go to sleep (in seconds) -> 30 minutes

void drawHeader(const String& leftText, const String& rightText) {
    display.fillRect(0, 0, display.width(), 30, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(10, 20);
    display.print(leftText);
    
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(rightText, 0, 0, &x, &y, &w, &h);
    display.setCursor(display.width() - w - 10, 20);
    display.print(rightText);
    display.setTextColor(GxEPD_BLACK);
}

void setup() {
    Serial.begin(115200);

    // --- Connect to WiFi ---
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    int wifi_retries = 0;
    while (WiFi.status() != WL_CONNECTED && wifi_retries < 20) {
        delay(500);
        Serial.print(".");
        wifi_retries++;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nWiFi Connection Failed. Entering deep sleep.");
        esp_deep_sleep_start();
    }
    Serial.println("\nConnected to WiFi!");

    // --- Initialize Display ---
    display.init(115200);
    display.setRotation(1); // 1 = landscape
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    
    // --- Fetch Data from API ---
    HTTPClient http;
    http.begin(api_url);
    int httpCode = http.GET();

    if (httpCode > 0) {
        String payload = http.getString();
        JsonDocument doc;
        deserializeJson(doc, payload);

        // --- Draw on Display ---
        display.firstPage();
        do {
            display.fillScreen(GxEPD_WHITE);

            // Header
            String dateStr = doc["date"];
            String nextEvent = "NEXT: " + String(doc["next_event"]["title"]);
            drawHeader(dateStr, nextEvent);

            // Weather & AQI
            display.setCursor(10, 60);
            display.print("Weather: " + String(doc["weather"]["temp"]) + "F " + String(doc["weather"]["icon"]));
            display.setCursor(10, 80);
            display.print("AQI: " + String(doc["aqi"]["value"]) + " (" + String(doc["aqi"]["label"]) + ")");

            // Vertical Separator
            display.fillRect(400, 40, 2, 440, GxEPD_BLACK);

            // Today's Todos
            display.setCursor(420, 60);
            display.print("TODAY'S TODOS");
            JsonArray todos = doc["todos"];
            int yPos = 80;
            for (JsonVariant v : todos) {
                display.setCursor(420, yPos);
                display.print("- " + v.as<String>());
                yPos += 20;
            }
            
            // Custom Quote
            display.setCursor(10, 200);
            display.print("\"" + doc["quote"].as<String>() + "\"");


        } while (display.nextPage());

    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        display.firstPage();
        do {
            display.fillScreen(GxEPD_WHITE);
            drawHeader("Error", "Could not fetch data");
            display.setCursor(10, 60);
            display.print("Failed to connect to API.");
            display.setCursor(10, 80);
            display.print("Check Serial Monitor for details.");
        } while (display.nextPage());
    }

    http.end();
    
    // --- Go to Sleep ---
    Serial.println("Display updated. Going to sleep now.");
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
}

void loop() {
    // This part is not used due to deep sleep.
}
