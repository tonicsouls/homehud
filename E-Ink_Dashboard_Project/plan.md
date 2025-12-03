# E-Ink Dashboard Project Plan

This project will create a personalized e-ink dashboard using a Seeed Studio reTerminal E1001. The dashboard will display information from Google Calendar and Google Tasks.

## Phase 1: The "Middleman" (Google Apps Script)

This phase focuses on creating a web-accessible API that provides the data for the e-ink display.

1.  **Create Google Apps Script:**
    *   Go to `script.google.com`.
    *   Create a new script.
2.  **Implement Script Logic:**
    *   Fetch upcoming events from Google Calendar.
    *   Fetch tasks from Google Tasks.
    *   (Optional) Add logic for personalized data, like the "Isaac's Aligners" counter.
    *   Format the data into a clean JSON object.
3.  **Deploy as Web App:**
    *   Deploy the script as a Web App.
    *   Set access to "Anyone".
    *   Save the generated Web App URL.

## Phase 2: The Firmware (ESP32-S3)

This phase focuses on programming the E1001 device to consume the data from the Google Apps Script.

1.  **Setup Development Environment:**
    *   Install VS Code.
    *   Install the PlatformIO IDE extension in VS Code.
2.  **Create PlatformIO Project:**
    *   Create a new PlatformIO project.
    *   Select "Espressif ESP32-S3-DevKitC-1" as the board.
    *   Select "Arduino" as the framework.
3.  **Add Library Dependencies:**
    *   Add the following libraries to `platformio.ini`:
        *   `bblanchon/ArduinoJson`
        *   `zinggjm/GxEPD2`
4.  **Implement C++ Sketch:**
    *   **Wi-Fi Connection:** Connect the device to your Wi-Fi network.
    *   **HTTP Request:** Make an HTTPS GET request to the Google Apps Script URL.
    *   **JSON Parsing:** Parse the JSON response using the ArduinoJson library.
    *   **Display Logic:** Use the GxEPD2 library to:
        *   Clear the display.
        *   Draw the date, time, calendar events, and tasks on the screen.
        *   Update the display.
    *   **Deep Sleep:** Put the device into deep sleep for a specified interval (e.g., 30 minutes) to conserve power.

## Phase 3: Content and Layout

This phase focuses on the design of the information displayed on the screen.

1.  **Define Content Hierarchy:**
    *   **Zone A (Anchor):** Essential information (Date, Time, Weather).
    *   **Zone B (Agenda):** "What's Next" (Next Meeting, To-Do List).
    *   **Zone C (Context):** Background information (Inspirational quotes, counters).
2.  **Finalize Content Modules:**
    *   Decide on the specific data points to display (e.g., AQI, family counters).
3.  **Implement Layout in Firmware:**
    *   Translate the layout design into code in the C++ sketch.
