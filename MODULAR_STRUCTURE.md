# HOMEHUD - Modular Dashboard System

A modular e-ink dashboard system designed for the **reTerminal E1001** (7.5" e-paper display) using **SenseCraft HMI**. Each module is a self-contained section that can be independently deployed and managed.

## 🎯 Project Structure

```
HOMEHUD/
├── isaac-words/              ← Self-contained module
│   ├── index.html            (Documentation)
│   ├── data/
│   │   └── isaac-words.json  (Master word list)
│   └── templates/
│       ├── isaac-words-random.json
│       ├── isaac-words-grade1.json
│       ├── isaac-words-grade2.json
│       ├── isaac-words-daily.json
│       └── isaac-words-simple.json
│
├── pokemon-news/             ← Self-contained module
│   ├── index.html            (Documentation)
│   ├── data/
│   │   └── [RSS feed data]
│   └── templates/
│       ├── pokemon-beach-news-updated.json
│       └── pokemon-beach-news-base.json
│
├── index.html                (Main dashboard hub)
├── isaac_word_generator.py   (Generates isaac-words templates)
├── rss_feed_updater.py       (Updates pokemon-news templates)
├── refresh-quotes.bat        (Auto-refresh scheduling)
└── refresh-rss-feeds.bat     (Auto-refresh scheduling)
```

## 📦 Modules

### 1. Isaac's Words (✏️)
**Purpose:** Daily vocabulary learning with emojis for Isaac (grades 1-2)

**Live URL:**
- Dashboard: https://tonicsouls.github.io/homehud/isaac-words/
- Random Word: https://tonicsouls.github.io/homehud/isaac-words/templates/isaac-words-random.json
- Grade 1 Only: https://tonicsouls.github.io/homehud/isaac-words/templates/isaac-words-grade1.json
- Grade 2 Only: https://tonicsouls.github.io/homehud/isaac-words/templates/isaac-words-grade2.json
- Daily (Sequential): https://tonicsouls.github.io/homehud/isaac-words/templates/isaac-words-daily.json

**Data:**
- 30 vocabulary words (20 Grade 1, 10 Grade 2)
- Each word includes: emoji, definition, example sentence, category
- Stored in: `isaac-words/data/isaac-words.json`

**Auto-Update:**
```bash
python isaac_word_generator.py
```
Generates fresh templates with random/daily selections from the master word list.

---

### 2. Pokemon Beach News (🔥)
**Purpose:** Live-updating community news from Pokemon Beach forums

**Live URL:**
- Dashboard: https://tonicsouls.github.io/homehud/pokemon-news/
- News Feed: https://tonicsouls.github.io/homehud/pokemon-news/templates/pokemon-beach-news-updated.json

**Features:**
- Fetches latest 3-4 articles from Pokemon Beach RSS
- Auto-updates every 30 minutes
- Article summaries (200 char max)

**Auto-Update:**
```bash
python rss_feed_updater.py
```
Fetches latest RSS entries and generates updated template.

---

## 🚀 Quick Start

### Add to SenseCraft HMI

1. Open **SenseCraft HMI** on your device
2. Select **"Web Content"** feature
3. Paste one of the **Live URLs** above
4. The template will auto-generate and display

### Example URLs to Try

```
Isaac's Words (Random):
https://tonicsouls.github.io/homehud/isaac-words/templates/isaac-words-random.json

Pokemon News:
https://tonicsouls.github.io/homehud/pokemon-news/templates/pokemon-beach-news-updated.json
```

---

## 🔄 Auto-Update Setup

### Option 1: Windows Batch Scripts (Recommended)

Each script auto-refreshes content at regular intervals.

**Isaac's Words (5-minute updates):**
```bash
.\refresh-quotes.bat
```

**Pokemon News (30-minute updates):**
```bash
.\refresh-rss-feeds.bat
```

Run both in separate terminal windows to keep both modules updated.

### Option 2: GitHub Actions (Future Enhancement)

For true automatic updates without running local scripts, GitHub Actions can be configured to:
- Run `isaac_word_generator.py` daily
- Run `rss_feed_updater.py` every 30 minutes
- Commit and push updates automatically

---

## 📝 Data Files

### Isaac's Words Master Data
```json
isaac-words/data/isaac-words.json
```

Structure:
```json
{
  "words": [
    {
      "id": 1,
      "word": "Apple",
      "emoji": "🍎",
      "definition": "A red or green fruit...",
      "example": "I eat an apple...",
      "grade": 1,
      "category": "Food",
      "hint": "Starts with 'A'"
    },
    ...
  ],
  "metadata": {
    "total_words": 30,
    "grade_1_words": 20,
    "grade_2_words": 10
  }
}
```

---

## 🛠️ Python Scripts

### isaac_word_generator.py
Generates 4 template variants from master word list:

```bash
python isaac_word_generator.py
```

**Generates:**
- `isaac-words-random.json` - Random word each time
- `isaac-words-grade1.json` - Grade 1 words only
- `isaac-words-grade2.json` - Grade 2 words only
- `isaac-words-daily.json` - Sequential daily words

### rss_feed_updater.py
Fetches Pokemon Beach RSS and generates template:

```bash
python rss_feed_updater.py
```

**Requires:**
```bash
pip install feedparser
```

**Generates:**
- `pokemon-news/templates/pokemon-beach-news-updated.json`

---

## 📊 Stats

- **Isaac's Words:** 30 vocabulary words + 4 template variants
- **Pokemon News:** Live RSS feed with 3-4 articles
- **Display:** 800×480 pixels, e-paper (5-min refresh)
- **Hosting:** GitHub Pages (free, static)
- **Update Frequency:** 5 min (quotes), 30 min (news)

---

## 🔗 GitHub Repository

**Repository:** https://github.com/tonicsouls/homehud

**Main Index:** https://tonicsouls.github.io/homehud/

---

## 📋 Future Enhancements

- [ ] Scale Isaac's Words to 365 words (one per day/year)
- [ ] Pikalytics Pokemon competitive data scraper
- [ ] GitHub Actions for true daily automation
- [ ] Weather dashboard module
- [ ] Calendar events module
- [ ] Template composition UI

---

## ⚙️ Requirements

- **Hardware:** Seeed reTerminal E1001 (or any device running SenseCraft HMI)
- **Software:** Python 3.8+, git, feedparser library
- **Hosting:** GitHub Pages (free)
- **Display:** SenseCraft HMI with Web Content feature

---

## 📞 Support

Each module has its own `index.html` with detailed setup instructions. Visit:

- Isaac's Words Help: https://tonicsouls.github.io/homehud/isaac-words/
- Pokemon News Help: https://tonicsouls.github.io/homehud/pokemon-news/

---

**Last Updated:** December 2, 2025
