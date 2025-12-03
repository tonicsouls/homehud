# HOMEHUD Status Report & Next Steps

**Repository:** https://github.com/tonicsouls/homehud.git
**Live Site:** (GitHub Pages - enable in settings)
**Last Updated:** December 2, 2025

---

## 🎯 Your Questions Answered

### Q1: Does the quote template refresh every 5 minutes?
**Current Status:** ❌ No - templates are static until manually updated

**Why:** SenseCraft displays JSON as-is. We need to:
1. Update the JSON file regularly
2. Tell SenseCraft to reload it
3. Or have SenseCraft fetch from a live URL

**Solutions (Pick One):**

**Option A: Windows Task Scheduler (Simplest for you)**
- Run `refresh-quotes.bat` continuously
- Updates `templates/quotes/rotating-quotes-*-updated.json` every 5 mins
- SenseCraft sees new quotes when dashboard refreshes
- ✅ Works today, ❌ Need PC running

**Option B: GitHub Pages (Best long-term)**
- Push quotes to GitHub automatically (daily or hourly)
- SenseCraft fetches from: `https://tonicsouls.github.io/homehud/data/quotes/random.json`
- ✅ No PC needed running, ✅ Works everywhere, ❌ Takes ~1 hour to set up

**Option C: Local Web Server (Advanced)**
- Run Python Flask server on your PC
- Device polls local server every 5 minutes
- ✅ Real-time, ❌ PC must be always on

**Recommendation:** Start with Option A (simplest), upgrade to Option B (GitHub Pages) next week

---

### Q2: How can we teach Isaac new words everyday?

**Options:**
1. **Word of the Day Template** - New dashboard showing vocabulary
2. **Vocabulary CSV** - 365 words with definitions/examples/pronunciations
3. **Smart Integration** - Extract uncommon words from daily quotes
4. **Interactive Learning** - Track words learned, spaced repetition

**Before I build:** I need to know:
- How old is Isaac? (Reading level?)
- How many words per day? (1-5?)
- Format? (word + definition, context sentences, images?)
- Include pronunciation? (Text or audio?)
- Specific subjects? (General, science, languages?)

**Estimated Build Time:** 1-2 hours (depends on complexity)

---

### Q3: Can we organize existing templates?

**Current Chaos:**
```
templates/
  ├── quotes/ (organized)
  ├── news-feeds/
  ├── weather/
  ├── calendar/
  └── productivity/

display templateates and ideas/
  ├── sensecraft-pokemon-dark.json
  ├── sensecraft-pokemon-light.json
  ├── sensecraft-pokemon-v2.json
  ├── sensecraft-hackernews-dark.json
  ├── sensecraft-hackernews-v2.json
  ├── sensecraft-hackernews-v3.json
  └── sensecraft-dashboard-dark.json
```

**Better Structure:**
```
templates/
├── quotes/
│   ├── 2-quote-featured.json
│   ├── 4-quote-grid.json
│   └── README.md
├── news-feeds/
│   ├── hacker-news.json
│   ├── pokemon-beach.json
│   └── README.md
├── weather/
│   ├── simple.json
│   ├── detailed.json
│   └── README.md
├── calendar/
├── productivity/
├── TEMPLATES.md (master index)
└── archive/ (old drafts)
```

**Action Plan:**
1. Inventory all templates (5 mins)
2. Create standardized names (camelCase, descriptive)
3. Move & organize by type (15 mins)
4. Create TEMPLATES.md catalog with previews (15 mins)
5. Archive old versions (5 mins)
6. Push to GitHub (2 mins)

**Estimated Time:** 45 minutes total

---

## 📋 Task Execution Plan

### IMMEDIATE (Next 30 mins)
1. ✅ Push to GitHub - **DONE**
2. Enable GitHub Pages in repo settings (2 mins)
   - Go to: https://github.com/tonicsouls/homehud/settings/pages
   - Select "Deploy from a branch"
   - Branch: main, Folder: / (root)
   - Save and wait 2-3 minutes
3. Test live URLs (5 mins)
   ```
   https://tonicsouls.github.io/homehud/index.html
   https://tonicsouls.github.io/homehud/data/quotes/random.json
   ```
4. Start `refresh-quotes.bat` in background (1 click)
   - This runs `dashboard_updater.py` every 5 mins
   - Will update quote templates continuously
   - Stop with Ctrl+C

**Time: 10 mins total**

---

### SHORT TERM (This Week)

**Task 1: Quote Auto-Refresh** (30 mins)
```powershell
# Option A: Run refresh script
cd "c:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD"
.\refresh-quotes.bat

# This loops forever, updating quotes every 5 mins
# Keep this running in a terminal window
```

**Task 2: Organize Templates** (45 mins)
- [ ] Inventory all templates in both locations
- [ ] Create standardized folder structure
- [ ] Move and rename files
- [ ] Create TEMPLATES.md catalog
- [ ] Archive old versions
- [ ] Push to GitHub

**Task 3: Plan Isaac's Word System** (20 mins - discussion)
- What's his age/reading level?
- How many words per day?
- Format preference?
- Build date: This weekend?

---

### MEDIUM TERM (Next 2 Weeks)

**Task 4: Build Isaac's Daily Words** (2-3 hours)
- Create vocabulary system
- Build display template
- Generate word list
- Deploy to device

**Task 5: Pikalytics Scraper** (2-3 hours)
- Build web scraper
- Format Pokemon data
- Create template
- Deploy

---

## 🚀 Quick Start Commands

### Enable GitHub Pages (Do This Now)
1. Open: https://github.com/tonicsouls/homehud/settings/pages
2. Select "Deploy from a branch" 
3. Branch: `main`, Folder: `/ (root)`
4. Click Save
5. Wait 2-3 minutes, then test: https://tonicsouls.github.io/homehud/

### Start Auto-Refresh (Do This Now)
```powershell
cd "C:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD"
.\refresh-quotes.bat
```
Leave this terminal running - quotes update every 5 mins.

### Push Latest Changes
```powershell
git add -A
git commit -m "Your message here"
git push
```

---

## 📊 What's Live Now

✅ **Code Repository:** https://github.com/tonicsouls/homehud
✅ **Quote System:** 150 quotes, no duplicates, random selection
✅ **Templates:** 2-quote & 4-quote layouts
✅ **Auto-Refresh:** `refresh-quotes.bat` script ready
⏳ **GitHub Pages:** Ready to enable (3 settings clicks)
⏳ **Isaac's Words:** Design phase (waiting for requirements)
⏳ **Template Organization:** Ready (just needs execution)

---

## 📝 Next Actions

**For You (Right Now):**
1. Enable GitHub Pages (2 mins)
2. Test live website (2 mins)
3. Start refresh-quotes.bat (1 min)
4. Tell me Isaac's word learning requirements (5 mins)

**Then I Will:**
1. Organize template folder structure
2. Build Isaac's vocabulary system
3. Set up automated GitHub updates
4. Create Pikalytics scraper

---

**Questions? Concerns? Ready to proceed?**
