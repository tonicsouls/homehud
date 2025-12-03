# E1001 Calendar Display - Complete Setup Guide

## Overview
This creates a free, autonomous calendar display that updates even when your PC is off.

---

## Phase 1: Backend Setup (15 minutes)

### Step 1: Deploy Google Apps Script
1. Go to [script.google.com](https://script.google.com)
2. Click **New Project**
3. Delete default code and paste from `e1001-calendar-backend.gs`
4. Name it: "E1001 Calendar API"

### Step 2: Enable Google Tasks API
1. Click **Services** (+ icon on left sidebar)
2. Search "Google Tasks API"
3. Click **Add**

### Step 3: Test It
1. Click **Run** > Select `testAPI`
2. Grant permissions when prompted
3. Check **Execution log** - you should see JSON output

### Step 4: Deploy as Web App
1. Click **Deploy** > **New deployment**
2. Click **Select type** > **Web app**
3. Settings:
   - Description: "E1001 Display API v1"
   - Execute as: **Me**
   - Who has access: **Anyone**
4. Click **Deploy**
5. **COPY THE WEB APP URL** (starts with `https://script.google.com/macros/s/...`)

---

## Phase 2: Hardware Setup (30 minutes)

### Step 1: Install VS Code Extensions
1. Open VS Code
2. Install **PlatformIO IDE** extension
3. Restart VS Code

### Step 2: Create Project
1. Click PlatformIO icon (alien head)
2. **New Project**
   - Name: `e1001-display`
   - Board: `Espressif ESP32-S3-DevKitC-1`
   - Framework: `Arduino`

### Step 3: Configure Dependencies
Edit `platformio.ini` and add:

```ini
lib_deps =
    bblanchon/ArduinoJson @ ^7.0.0
    zinggjm/GxEPD2 @ ^1.5.9
```

### Step 4: Upload Firmware
(Firmware code will be in next step - awaiting your backend URL)

---

## Phase 3: Voice Integration (Already Works!)

### How It Works
1. Say: **"OK Google, add task: Change Isaac's aligners tomorrow"**
2. Google Assistant → Adds to Google Tasks
3. Your script reads it automatically
4. E1001 displays it within 30 minutes

### No Extra Setup Needed
Your Google account is already linked!

---

## Content Layout (7.5" E-Ink Screen)

```
┌─────────────────────────────────────────────────────────────┐
│  WEDNESDAY, DEC 1                  NEXT: Sync w/ Team       │
│  1:02 PM                           10:00 AM                 │
│                                                             │
│  Weather: 68°F ☁                   TODAY'S TODOS            │
│  AQI: 45 (Good)                    □ Update CSS             │
│                                    □ Review code            │
│  ─────────────────────────────────                         │
│                                    ISAAC'S ALIGNERS         │
│  "Calm Mind,                       Day 41 / 730             │
│   Driven Performance"              Next change: Tuesday     │
└─────────────────────────────────────────────────────────────┘
```

---

## Cost Breakdown

| Service | Cost |
|---------|------|
| Google Apps Script Hosting | **$0** |
| Google Calendar API | **$0** |
| Google Tasks API | **$0** |
| VS Code + PlatformIO | **$0** |
| Libraries (ArduinoJson, GxEPD2) | **$0** |
| **TOTAL** | **$0/month** |

---

## Next Steps

✅ **YOU ARE HERE**: Backend script created  
⬜ Deploy script and get URL  
⬜ Create firmware with your URL  
⬜ Flash to E1001  
⬜ Test voice commands  

---

## Troubleshooting

### "Script not authorized"
- Go to script.google.com > Your project > Run > Grant permissions

### "Tasks API not found"
- Make sure you added Tasks API in Services

### "Device won't connect"
- Check WiFi credentials in firmware
- Verify URL is correct (no extra spaces)

### "Screen shows old data"
- Device is in deep sleep
- Wait 30 minutes for next wake cycle
- Or press reset button to force update

---

## Customization Ideas

- [ ] Add OpenWeatherMap API for real weather
- [ ] Track Nigel's code commits via GitHub API
- [ ] Add family birthday countdowns
- [ ] Display medication reminders
- [ ] Show gym streak counter

---

**Questions?** The architecture is designed so you can edit the Google Script in your browser without re-flashing the device!
