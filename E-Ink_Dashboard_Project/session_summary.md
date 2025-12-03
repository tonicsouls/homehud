# Project Save Point: E-Ink Dashboard

This file summarizes our progress as of Sunday, November 30, 2025. You can use this to resume our session on a different machine.

## Project Goal
To create a personalized, always-on e-ink dashboard using a Seeed E1001 display. The dashboard will pull live data from Google Calendar and Google Tasks and will operate autonomously, even when your computer is off.

## Current Status: Phase 1 Complete

We have successfully completed the backend setup for the project.

- **Action:** Created and deployed a Google Apps Script to act as a free, cloud-hosted API.
- **Result:** The script fetches your calendar events, tasks, and other custom data, serving it as a JSON feed.

## Key Data Recorded

The following critical piece of information has been generated and saved:

- **Google Apps Script Web App URL:** `https://script.google.com/macros/s/AKfycbztMUdiwwnV4cJOIx6hk-FE8zhdbthOoI6a73tQ1C35NySe-_NRNXkuSdNyD7Lzjt7W9g/exec`

## Immediate Next Steps: Phase 2

We are ready to begin **Phase 2: Hardware Setup**. When you are set up on your new laptop, our next action will be:

1.  **Open VS Code.**
2.  **Install the PlatformIO IDE extension.**
3.  **Create a new PlatformIO Project** with the following settings:
    - Name: `e1001-display`
    - Board: `Espressif ESP32-S3-DevKitC-1`
    - Framework: `Arduino`
4.  **Add Dependencies:** Edit the `platformio.ini` file to include the necessary libraries:
    ```ini
    lib_deps =
        bblanchon/ArduinoJson @ ^7.0.0
        zinggjm/GxEPD2 @ ^1.5.9
    ```
5.  **Generate Firmware:** Once the above is complete, I will provide the C++ firmware code (for your `main.cpp` file), which will include your unique Web App URL.

You are all set to switch devices. Just let me know when you're ready to proceed with these steps.

---

## Future Features / Version 2.0 Vision

This section captures the advanced features we've discussed. These can be implemented after the initial version is running.

### Dynamic Daily Content
- **Quote of the Day:** Modify the Google Apps Script to fetch a new quote daily from an external API.
- **Personal Prompt of the Day:** The script will pull a daily prompt from a dedicated Google Sheet or text file in Google Drive.
- **Page-a-Day Reader:**
    - **Source:** A `.txt` file of a public domain book (from Project Gutenberg) stored in your Google Drive.
    - **Logic:** The Google Apps Script will track your progress and serve one "page" of text to the display each day.

### AI-Powered Journal Integration ("The Gemini Protocol")
This is a repeatable, AI-driven workflow to extract your top priorities directly from your handwritten journal.

1.  **User Protocol:** You take a photo of your daily journal entry and save it to a specific folder in Google Drive.
2.  **The "Gemini Agent" (Backend):**
    - The Google Apps Script will monitor this folder.
    - Upon detecting a new image, it will send the image to the **Gemini API (Vision Model)**.
    - The prompt to Gemini will be: *"Analyze this image of a handwritten journal page and extract the top 3 most important tasks or priorities. Return them as a simple list."*
3.  **Display:** The script will process Gemini's response and display your "Top 3 from Journal" on the e-ink screen.
