# HOMEHUD Task List

## High Priority - Device & Quote Integration

### 1. ⏱️ Quote Template Auto-Refresh (CRITICAL)
**Problem:** Templates don't auto-update - quotes are static until manually regenerated
**Solution Needed:** 
- Create scheduled task to run `dashboard_updater.py` every 5 minutes
- OR: Build local HTTP server that SenseCraft polls
- OR: Push to GitHub Pages, SenseCraft fetches from URL

**Dependency:** Clarify refresh mechanism with device
**Estimated Time:** 30 mins

### 2. 🔗 Deploy to GitHub Pages
**Status:** Repository ready at https://github.com/tonicsouls/homehud.git
**Action Items:**
- Push local files to GitHub (5 mins)
- Enable GitHub Pages in settings (2 mins)
- Update data URLs in SenseCraft templates (10 mins)
- Test live quote endpoint (5 mins)

**Estimated Time:** 20-30 mins

### 3. 🗂️ Organize Existing Templates
**Current Structure Issues:**
- Templates scattered in multiple locations (templates/, display templateates and ideas/)
- No clear naming convention
- Mix of draft, working, and finalized versions

**Action Items:**
- Inventory all existing templates (5 mins)
- Create folder structure: /templates/{media-type}/{template-name}/
- Move & organize (News, Quotes, Weather, Calendar, Productivity)
- Create template catalog/README with thumbnails
- Delete old drafts/backups

**Estimated Time:** 45 mins - 1 hour

---

## Medium Priority - Content & Learning

### 4. 📚 Isaac's Daily Word Learning System
**Goal:** Teach Isaac new words every day
**Possible Implementation:**
- Option A: Vocabulary CSV → JSON word list with definitions/examples
- Option B: RSS feed from vocabulary/language site
- Option C: AI-generated word list with contextual sentences
- Option D: Combine with existing quote system (extract uncommon words)

**To Discuss:**
- What's Isaac's age/reading level?
- Display format preference? (word + definition, word of day, challenge format)
- How many words per day?
- Include pronunciation? Translation?

**Estimated Time:** 1-2 hours (depends on approach)

---

## Lower Priority - Enhancements

### 5. 🔄 Template Refresh Mechanism
**Options:**
- A) Windows Task Scheduler → Python script every 5 mins
- B) Local Python web server on PC/device
- C) GitHub Actions → auto-update repo daily
- D) Device-side script (if device supports Python/cron)

**Best Practice:** GitHub Pages (Option C) - no local scheduling needed

**Estimated Time:** 1 hour

### 6. 📊 Pikalytics Pokemon Data Scraper (Nigel's Request)
**Status:** Noted in FEATURE_REQUESTS.md
**Blocked By:** Quote system stabilization
**Estimated Time:** 2-3 hours

### 7. 🎨 Dashboard UI Improvements
- Create responsive template editor
- Add visual template previews
- Build template composition tool
- Theme generator

**Estimated Time:** 3+ hours

---

## Completed ✅

- ✅ Quote data processing (150 quotes → 3 JSON files)
- ✅ Quote rotation logic (no duplicates)
- ✅ Dashboard templates (2-quote, 4-quote layouts)
- ✅ Template updater script (dashboard_updater.py)
- ✅ GitHub Pages setup (generate_github_pages.py)
- ✅ Git repository initialized
- ✅ SenseCraft device deployment

---

## Recommended Next Steps (In Order)

1. **TODAY** → Deploy to GitHub Pages (20 mins)
2. **TODAY** → Set up auto-refresh mechanism (30 mins)
3. **THIS WEEK** → Organize template folder structure (1 hour)
4. **THIS WEEK** → Plan Isaac's word learning system (clarify requirements)
5. **LATER** → Build Pikalytics scraper
6. **LATER** → Advanced template tools

---

**Total Effort to Core Functionality:** 2-3 hours
**Total Effort (+ Isaac + Organization):** 4-5 hours
