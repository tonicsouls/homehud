#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMono9pt7b.h>

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

// Button Pins (common ESP32-S3 GPIO buttons - may need adjustment)
// Try these first, adjust based on your hardware
#define BTN_LEFT   4   // Left button / Previous page
#define BTN_RIGHT  5   // Right button / Next page  
#define BTN_SELECT 6   // Select/Refresh button
#define BTN_BOOT   0   // Boot button (usually GPIO0 on ESP32)

// Use the 7.5-inch GDEY075T7 display (800x480) - correct driver for reTerminal E1001
GxEPD2_BW<GxEPD2_750_GDEY075T7, GxEPD2_750_GDEY075T7::HEIGHT> display(GxEPD2_750_GDEY075T7(EPD_CS, EPD_DC, EPD_RST, EPD_BUSY));

// --- WiFi & API Configuration ---
const char* ssid = "Omni.here";
const char* password = "8176761765";
const String api_url = "https://script.google.com/macros/s/AKfycbztMUdiwwnV4cJOIx6hk-FE8zhdbthOoI6a73tQ1C35NySe-_NRNXkuSdNyD7Lzjt7W9g/exec";

// --- Page Navigation ---
enum Page { PAGE_HOME, PAGE_TODOS, PAGE_ALIGNERS, PAGE_INFO, PAGE_COUNT };
volatile int currentPage = PAGE_HOME;
volatile bool needsRefresh = true;

// --- Deep Sleep Configuration ---
#define uS_TO_S_FACTOR 1000000ULL
#define TIME_TO_SLEEP  1800       // 30 minutes

// --- Global data cache ---
JsonDocument cachedData;
bool dataLoaded = false;

// --- Button debounce ---
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 300;

// --- Helper: Safe string extraction from JSON ---
String safeString(JsonVariant v, const char* fallback = "") {
    if (v.isNull()) return String(fallback);
    return String(v.as<const char*>());
}

int safeInt(JsonVariant v, int fallback = 0) {
    if (v.isNull()) return fallback;
    if (v.is<int>()) return v.as<int>();
    if (v.is<const char*>()) return atoi(v.as<const char*>());
    return fallback;
}

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

void drawFooter() {
    int footerY = display.height() - 25;
    display.fillRect(0, footerY, display.width(), 25, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&FreeMono9pt7b);
    
    // Page indicator
    String pageInfo = "Page " + String(currentPage + 1) + "/" + String(PAGE_COUNT);
    display.setCursor(10, footerY + 17);
    display.print(pageInfo);
    
    // Navigation hints
    String navHint = "[<] Prev  [>] Next  [o] Refresh";
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(navHint, 0, 0, &x, &y, &w, &h);
    display.setCursor(display.width() - w - 10, footerY + 17);
    display.print(navHint);
    
    display.setTextColor(GxEPD_BLACK);
}

// ========================================
// Page Drawing Functions
// ========================================

void drawHomePage() {
    display.fillScreen(GxEPD_WHITE);
    
    // Header
    String dateStr = safeString(cachedData["date"], "Loading...");
    String nextEventTitle = safeString(cachedData["next_event"]["title"], "No events");
    String nextEventTime = safeString(cachedData["next_event"]["time"], "");
    String headerRight = nextEventTime.length() > 0 ? nextEventTime + " " + nextEventTitle : nextEventTitle;
    drawHeader(dateStr, headerRight);
    
    // Left Column - Weather & Info
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, 60);
    display.print("WEATHER");
    
    display.setFont(&FreeMonoBold9pt7b);
    // Weather - handle both string "68°F" and nested object formats
    String weatherTemp = safeString(cachedData["weather"]["temp"], "N/A");
    String weatherCond = safeString(cachedData["weather"]["condition"], "");
    int weatherAqi = safeInt(cachedData["weather"]["aqi"], 0);
    
    display.setCursor(10, 85);
    display.print("Temp: " + weatherTemp);
    display.setCursor(10, 105);
    display.print("Cond: " + weatherCond);
    if (weatherAqi > 0) {
        display.setCursor(10, 125);
        display.print("AQI: " + String(weatherAqi));
    }
    
    // Horizontal separator
    display.fillRect(10, 145, 380, 2, GxEPD_BLACK);
    
    // Isaac's Aligners Section
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, 175);
    display.print("ISAAC'S ALIGNERS");
    
    display.setFont(&FreeMonoBold9pt7b);
    int alignerDay = safeInt(cachedData["isaac_aligners"]["day_current"], 0);
    int alignerTotal = safeInt(cachedData["isaac_aligners"]["day_total"], 730);
    int alignerPercent = safeInt(cachedData["isaac_aligners"]["percent_complete"], 0);
    String alignerMsg = safeString(cachedData["isaac_aligners"]["message"], "");
    String alignerNext = safeString(cachedData["isaac_aligners"]["next_change"], "");
    
    display.setCursor(10, 200);
    display.print("Day " + String(alignerDay) + " of " + String(alignerTotal));
    
    // Progress bar
    display.drawRect(10, 210, 200, 20, GxEPD_BLACK);
    int progressWidth = (alignerPercent * 196) / 100;
    display.fillRect(12, 212, progressWidth, 16, GxEPD_BLACK);
    display.setCursor(220, 225);
    display.print(String(alignerPercent) + "%");
    
    display.setCursor(10, 255);
    display.print("Next: " + alignerNext);
    if (alignerMsg.length() > 0) {
        display.setCursor(10, 275);
        display.print(alignerMsg);
    }
    
    // Horizontal separator
    display.fillRect(10, 295, 380, 2, GxEPD_BLACK);
    
    // Quote of the day
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, 325);
    display.print("DAILY MANTRA");
    
    display.setFont(&FreeMono9pt7b);
    String quote = safeString(cachedData["motivational_quote"], "Build with Purpose");
    display.setCursor(10, 350);
    display.print("\"" + quote + "\"");
    
    // Vertical Separator
    display.fillRect(400, 35, 2, display.height() - 60, GxEPD_BLACK);
    
    // Right Column - Today's Todos (preview)
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(420, 60);
    display.print("TODAY'S TODOS");
    
    display.setFont(&FreeMonoBold9pt7b);
    JsonArray todos = cachedData["todos"];
    int yPos = 90;
    int todoCount = 0;
    for (JsonVariant v : todos) {
        if (todoCount >= 5) {  // Show max 5 on home page
            display.setCursor(420, yPos);
            display.print("... more on TODO page");
            break;
        }
        display.setCursor(420, yPos);
        String todoText = safeString(v, "");
        if (todoText.length() > 35) {
            todoText = todoText.substring(0, 32) + "...";
        }
        display.print("- " + todoText);
        yPos += 22;
        todoCount++;
    }
    
    if (todoCount == 0) {
        display.setCursor(420, yPos);
        display.print("No tasks pending!");
    }
    
    // Footer
    drawFooter();
}

void drawTodosPage() {
    display.fillScreen(GxEPD_WHITE);
    drawHeader("TODOS", safeString(cachedData["date"], ""));
    
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, 60);
    display.print("ALL TASKS");
    
    display.setFont(&FreeMonoBold9pt7b);
    JsonArray todos = cachedData["todos"];
    int yPos = 90;
    int todoCount = 0;
    
    for (JsonVariant v : todos) {
        display.setCursor(10, yPos);
        String todoText = safeString(v, "");
        // Checkbox style
        display.drawRect(10, yPos - 12, 14, 14, GxEPD_BLACK);
        display.setCursor(30, yPos);
        if (todoText.length() > 70) {
            todoText = todoText.substring(0, 67) + "...";
        }
        display.print(todoText);
        yPos += 28;
        todoCount++;
        
        if (yPos > display.height() - 50) break;  // Don't overflow
    }
    
    if (todoCount == 0) {
        display.setCursor(10, yPos);
        display.print("No tasks pending - enjoy your day!");
    }
    
    drawFooter();
}

void drawAlignersPage() {
    display.fillScreen(GxEPD_WHITE);
    drawHeader("ALIGNERS", safeString(cachedData["date"], ""));
    
    // Large title
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, 70);
    display.print("ISAAC'S INVISALIGN PROGRESS");
    
    // Big progress display
    int alignerDay = safeInt(cachedData["isaac_aligners"]["day_current"], 0);
    int alignerTotal = safeInt(cachedData["isaac_aligners"]["day_total"], 730);
    int alignerPercent = safeInt(cachedData["isaac_aligners"]["percent_complete"], 0);
    String alignerMsg = safeString(cachedData["isaac_aligners"]["message"], "");
    String alignerNext = safeString(cachedData["isaac_aligners"]["next_change"], "");
    
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(50, 140);
    display.print("Day " + String(alignerDay) + " of " + String(alignerTotal));
    
    // Large progress bar
    display.drawRect(50, 160, 500, 40, GxEPD_BLACK);
    int progressWidth = (alignerPercent * 496) / 100;
    display.fillRect(52, 162, progressWidth, 36, GxEPD_BLACK);
    
    display.setCursor(570, 190);
    display.print(String(alignerPercent) + "%");
    
    // Stats
    display.setCursor(50, 240);
    display.print("Next Change: " + alignerNext);
    
    display.setCursor(50, 280);
    display.print("Status: " + alignerMsg);
    
    // Days remaining
    int daysRemaining = alignerTotal - alignerDay;
    display.setCursor(50, 320);
    display.print("Days Remaining: " + String(daysRemaining));
    
    // Estimated completion
    display.setCursor(50, 360);
    display.print("Target: ~" + String(daysRemaining / 30) + " months to go!");
    
    drawFooter();
}

void drawInfoPage() {
    display.fillScreen(GxEPD_WHITE);
    drawHeader("SYSTEM INFO", safeString(cachedData["time"], ""));
    
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, 60);
    display.print("DASHBOARD STATUS");
    
    display.setFont(&FreeMonoBold9pt7b);
    int yPos = 95;
    
    display.setCursor(10, yPos);
    display.print("WiFi: " + WiFi.localIP().toString());
    yPos += 25;
    
    display.setCursor(10, yPos);
    display.print("Signal: " + String(WiFi.RSSI()) + " dBm");
    yPos += 25;
    
    display.setCursor(10, yPos);
    display.print("SSID: " + String(ssid));
    yPos += 25;
    
    display.setCursor(10, yPos);
    display.print("Free Heap: " + String(ESP.getFreeHeap() / 1024) + " KB");
    yPos += 25;
    
    display.setCursor(10, yPos);
    display.print("Display: 800x480 E-Paper");
    yPos += 25;
    
    display.setCursor(10, yPos);
    display.print("Refresh: Every 30 min");
    yPos += 40;
    
    // Separator
    display.fillRect(10, yPos, display.width() - 20, 2, GxEPD_BLACK);
    yPos += 30;
    
    display.setFont(&FreeMonoBold12pt7b);
    display.setCursor(10, yPos);
    display.print("FUTURE PAGES (Coming Soon)");
    yPos += 30;
    
    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(10, yPos);
    display.print("- 5-Day Weather Forecast");
    yPos += 22;
    display.setCursor(10, yPos);
    display.print("- Google News RSS Feed");
    yPos += 22;
    display.setCursor(10, yPos);
    display.print("- Daily EPUB Reader");
    yPos += 22;
    display.setCursor(10, yPos);
    display.print("- Bible Verse of the Day");
    yPos += 22;
    display.setCursor(10, yPos);
    display.print("- Constitution Snippet");
    yPos += 22;
    display.setCursor(10, yPos);
    display.print("- Book 2 Daily Reading");
    
    drawFooter();
}

void drawCurrentPage() {
    display.firstPage();
    do {
        switch (currentPage) {
            case PAGE_HOME:
                drawHomePage();
                break;
            case PAGE_TODOS:
                drawTodosPage();
                break;
            case PAGE_ALIGNERS:
                drawAlignersPage();
                break;
            case PAGE_INFO:
                drawInfoPage();
                break;
            default:
                drawHomePage();
                break;
        }
    } while (display.nextPage());
}

void drawErrorPage(int httpCode, String errorMsg) {
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        drawHeader("ERROR", "API Failed");
        
        display.setFont(&FreeMonoBold12pt7b);
        display.setCursor(10, 70);
        display.print("Connection Error");
        
        display.setFont(&FreeMonoBold9pt7b);
        display.setCursor(10, 110);
        display.print("HTTP Code: " + String(httpCode));
        display.setCursor(10, 135);
        display.print("Error: " + errorMsg);
        display.setCursor(10, 175);
        display.print("WiFi: " + WiFi.localIP().toString());
        display.setCursor(10, 200);
        display.print("Signal: " + String(WiFi.RSSI()) + " dBm");
        display.setCursor(10, 240);
        display.print("Check Google Apps Script deployment");
        display.setCursor(10, 280);
        display.print("Will retry in 30 minutes...");
        
        drawFooter();
    } while (display.nextPage());
}

// ========================================
// Button Handlers
// ========================================

void IRAM_ATTR onLeftButton() {
    if (millis() - lastButtonPress > debounceDelay) {
        lastButtonPress = millis();
        currentPage = (currentPage - 1 + PAGE_COUNT) % PAGE_COUNT;
        needsRefresh = true;
    }
}

void IRAM_ATTR onRightButton() {
    if (millis() - lastButtonPress > debounceDelay) {
        lastButtonPress = millis();
        currentPage = (currentPage + 1) % PAGE_COUNT;
        needsRefresh = true;
    }
}

bool fetchData() {
    Serial.println("Fetching data from API...");
    Serial.println("URL: " + api_url);
    
    // Retry up to 3 times
    for (int attempt = 1; attempt <= 3; attempt++) {
        Serial.printf("Attempt %d of 3...\n", attempt);
        
        WiFiClientSecure client;
        client.setInsecure();  // Skip SSL certificate verification
        client.setTimeout(20000);  // 20 second timeout for SSL
        
        HTTPClient http;
        http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
        http.setTimeout(20000);  // 20 second timeout
        http.setReuse(false);  // Don't reuse connections
        
        // Add headers that Google Apps Script expects
        http.addHeader("Accept", "application/json");
        http.addHeader("User-Agent", "ESP32-E1001-Dashboard/1.0");
        
        Serial.println("Starting HTTPS connection...");
        bool beginResult = http.begin(client, api_url);
        if (!beginResult) {
            Serial.println("http.begin() failed!");
            http.end();
            delay(2000);
            continue;
        }
        
        Serial.println("Sending GET request...");
        int httpCode = http.GET();
        Serial.printf("HTTP Response code: %d\n", httpCode);
        
        if (httpCode == 200) {
            String payload = http.getString();
            Serial.println("API Response received!");
            Serial.println("Payload length: " + String(payload.length()));
            Serial.println(payload.substring(0, min(500, (int)payload.length())));  // Print first 500 chars
            
            DeserializationError error = deserializeJson(cachedData, payload);
            if (error) {
                Serial.print("JSON parse error: ");
                Serial.println(error.c_str());
                http.end();
                return false;
            }
            
            dataLoaded = true;
            http.end();
            Serial.println("Data loaded successfully!");
            return true;
        } else if (httpCode > 0) {
            // Got a response but not 200
            Serial.printf("[HTTP] Non-200 response: %d\n", httpCode);
            String errorBody = http.getString();
            Serial.println("Response body: " + errorBody.substring(0, min(200, (int)errorBody.length())));
            http.end();
            
            if (attempt == 3) {
                drawErrorPage(httpCode, "HTTP " + String(httpCode));
            }
        } else {
            // httpCode < 0 means connection error
            Serial.printf("[HTTP] Connection error: %s\n", http.errorToString(httpCode).c_str());
            Serial.println("WiFi status: " + String(WiFi.status()));
            Serial.println("WiFi IP: " + WiFi.localIP().toString());
            Serial.println("WiFi RSSI: " + String(WiFi.RSSI()));
            http.end();
            
            if (attempt == 3) {
                drawErrorPage(httpCode, http.errorToString(httpCode));
            }
        }
        
        delay(3000);  // Wait 3 seconds before retry
    }
    
    return false;
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("\n\n========================================");
    Serial.println("E1001 E-Paper Dashboard Starting...");
    Serial.println("========================================");

    // --- Setup Buttons ---
    pinMode(BTN_LEFT, INPUT_PULLUP);
    pinMode(BTN_RIGHT, INPUT_PULLUP);
    pinMode(BTN_SELECT, INPUT_PULLUP);
    pinMode(BTN_BOOT, INPUT_PULLUP);
    
    // Attach interrupts
    attachInterrupt(digitalPinToInterrupt(BTN_LEFT), onLeftButton, FALLING);
    attachInterrupt(digitalPinToInterrupt(BTN_RIGHT), onRightButton, FALLING);
    
    Serial.println("Buttons configured: LEFT=GPIO4, RIGHT=GPIO5, SELECT=GPIO6, BOOT=GPIO0");

    // --- Connect to WiFi ---
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);
    
    WiFi.mode(WIFI_STA);  // Station mode
    WiFi.disconnect();     // Clear any old connection
    delay(100);
    WiFi.begin(ssid, password);
    
    int wifi_retries = 0;
    while (WiFi.status() != WL_CONNECTED && wifi_retries < 40) {
        delay(500);
        Serial.print(".");
        wifi_retries++;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nWiFi Connection Failed!");
    } else {
        Serial.println("\nWiFi Connected!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
        Serial.print("Signal: ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
    }

    // --- Initialize Display ---
    Serial.println("Initializing E-Paper display...");
    SPI.begin(EPD_SCK, -1, EPD_MOSI, EPD_CS);
    display.init(115200, true, 2, false);
    display.setRotation(0);  // Landscape
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    Serial.println("Display initialized!");
    Serial.printf("Display size: %dx%d\n", display.width(), display.height());

    // --- Fetch Data ---
    if (WiFi.status() == WL_CONNECTED) {
        fetchData();
    }
    
    // --- Draw Initial Page ---
    if (dataLoaded) {
        drawCurrentPage();
    } else {
        drawErrorPage(-1, "No data loaded");
    }
    
    needsRefresh = false;
    Serial.println("Setup complete. Use buttons to navigate pages.");
    Serial.println("Left=Previous, Right=Next, Boot=Refresh");
}

void loop() {
    // Check if refresh is needed (button was pressed)
    if (needsRefresh && dataLoaded) {
        Serial.printf("Switching to page %d\n", currentPage);
        drawCurrentPage();
        needsRefresh = false;
    }
    
    // Check boot button for manual refresh
    if (digitalRead(BTN_BOOT) == LOW) {
        delay(50);  // Debounce
        if (digitalRead(BTN_BOOT) == LOW) {
            Serial.println("Boot button pressed - refreshing data...");
            if (fetchData()) {
                drawCurrentPage();
            }
            while (digitalRead(BTN_BOOT) == LOW) delay(10);  // Wait for release
        }
    }
    
    // Check select button for same action
    if (digitalRead(BTN_SELECT) == LOW) {
        delay(50);
        if (digitalRead(BTN_SELECT) == LOW) {
            Serial.println("Select button pressed - refreshing data...");
            if (fetchData()) {
                drawCurrentPage();
            }
            while (digitalRead(BTN_SELECT) == LOW) delay(10);
        }
    }
    
    delay(100);  // Small delay to prevent CPU hogging
}
