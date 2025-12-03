#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// ========================================
// reTerminal E1001 Pin Configuration
// ========================================
// SPI Pins for ESP32-S3 on reTerminal E1001
#define EPD_SCK    7   // SPI Clock
#define EPD_MOSI   9   // SPI MOSI (Data)
#define EPD_CS     10  // Chip Select
#define EPD_DC     11  // Data/Command
#define EPD_RST    12  // Reset
#define EPD_BUSY   13  // Busy (active LOW on E1001)

// Use the 7.5-inch GDEY075T7 display (800x480) - correct driver for reTerminal E1001
GxEPD2_BW<GxEPD2_750_GDEY075T7, GxEPD2_750_GDEY075T7::HEIGHT> display(GxEPD2_750_GDEY075T7(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

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

    // --- Initialize Display for reTerminal E1001 ---
    // The GxEPD2 library handles SPI internally
    // We need to manually configure the SPI pins before init
    SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);  // SCK=7, MISO=-1 (not used), MOSI=9, SS=10
    
    // Initialize display with: baud, initial=true, reset_duration=2 (for Waveshare boards), pulldown_rst_mode=false
    display.init(115200, true, 2, false);
    display.setRotation(0); // 0 = correct landscape orientation for reTerminal E1001
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);

    Serial.println("Display initialized!");
    
    // --- Fetch Data from API ---
    WiFiClientSecure client;
    client.setInsecure();  // Skip certificate verification for simplicity
    
    HTTPClient http;
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);  // Google Apps Script redirects
    http.begin(client, api_url);
    http.setTimeout(15000);  // 15 second timeout
    
    Serial.println("Fetching data from API...");
    int httpCode = http.GET();
    Serial.printf("HTTP Response code: %d\n", httpCode);

    if (httpCode > 0) {
        String payload = http.getString();
        JsonDocument doc;
        deserializeJson(doc, payload);

        // --- Draw on Display ---
        display.firstPage();
        do {
            display.fillScreen(GxEPD_WHITE);

            // Header
            String dateStr = doc["date"].as<const char*>();
            String nextEvent = "NEXT: " + String(doc["next_event"]["title"].as<const char*>());
            drawHeader(dateStr, nextEvent);

            // Weather & AQI
            display.setCursor(10, 60);
            display.print("Weather: " + String(doc["weather"]["temp"].as<int>()) + "F " + String(doc["weather"]["icon"].as<const char*>()));
            display.setCursor(10, 80);
            display.print("AQI: " + String(doc["aqi"]["value"].as<int>()) + " (" + String(doc["aqi"]["label"].as<const char*>()) + ")");

            // Vertical Separator
            display.fillRect(400, 40, 2, 440, GxEPD_BLACK);

            // Today's Todos
            display.setCursor(420, 60);
            display.print("TODAY'S TODOS");
            JsonArray todos = doc["todos"];
            int yPos = 80;
            for (JsonVariant v : todos) {
                display.setCursor(420, yPos);
                display.print(String("- ") + v.as<const char*>());
                yPos += 20;
            }
            
            // Custom Quote
            display.setCursor(10, 200);
            display.print(String("\"") + doc["quote"].as<const char*>() + "\"");


        } while (display.nextPage());

    } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        display.firstPage();
        do {
            display.fillScreen(GxEPD_WHITE);
            drawHeader("Error", "API Failed");
            display.setCursor(10, 60);
            display.print("HTTP Code: " + String(httpCode));
            display.setCursor(10, 80);
            display.print("Error: " + http.errorToString(httpCode));
            display.setCursor(10, 120);
            display.print("WiFi: " + WiFi.localIP().toString());
            display.setCursor(10, 160);
            display.print("Check Google Apps Script deployment");
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
