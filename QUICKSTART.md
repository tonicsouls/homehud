# HOMEHUD Quick Start - What You Need to Do NOW

## ✅ GitHub Pages Status
**LIVE & WORKING!** ✅ Status: 200 OK

### Your URL is READY to attach:
```
https://tonicsouls.github.io/homehud/data/words/isaac-words.json
```

### Other URLs Available:
```
# Quotes
https://tonicsouls.github.io/homehud/data/quotes/random.json
https://tonicsouls.github.io/homehud/data/quotes/quotes-part1.json
https://tonicsouls.github.io/homehud/data/quotes/quotes-part2.json
https://tonicsouls.github.io/homehud/data/quotes/quotes-part3.json

# Isaac's Words (4 variants)
https://tonicsouls.github.io/homehud/data/words/isaac-words.json (master list)
https://tonicsouls.github.io/homehud/templates/isaac-words-random.json (random word)
https://tonicsouls.github.io/homehud/templates/isaac-words-grade1.json (Grade 1)
https://tonicsouls.github.io/homehud/templates/isaac-words-grade2.json (Grade 2)
https://tonicsouls.github.io/homehud/templates/isaac-words-daily.json (daily seq)

# Homepage
https://tonicsouls.github.io/homehud/index.html
```

---

## What is `refresh-quotes.bat`?

**Simple answer:** A script that updates your quote templates every 5 minutes

**What it does:**
1. Runs `dashboard_updater.py` automatically
2. Generates new random quotes (no duplicates)
3. Updates template files
4. Repeats every 5 minutes (300 seconds)
5. Runs in a loop until you close the terminal

**Why you need it:**
- Without it = same quotes forever (static)
- With it = new quotes every 5 minutes (dynamic locally)
- Device refreshes → sees new quotes

**Use case:**
- Run on your PC while device is active
- Keep terminal window open in background
- Refresh-quotes.bat keeps generating new templates
- Device fetches updated templates every 5 min
- Isaac sees new words each refresh

---

## Your Current Setup

✅ **GitHub Pages:** LIVE & accessible
✅ **Isaac's words:** 30 words with emojis
✅ **Quote system:** 150 quotes, no duplicates
✅ **Templates:** All generated and ready
✅ **URLs:** All publicly accessible

---

## What You Need to Do - 3 Options

### OPTION 1: Use Local Refresh (Simplest Now)
**For PC + Device on same WiFi:**

1. Keep PC on
2. Run this in PowerShell:
```powershell
cd "C:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD"
.\refresh-quotes.bat
```
3. Leave terminal running (minimized in background)
4. Import template into SenseCraft
5. Device refreshes every 5 mins = new quotes + words

**Pros:** Works immediately, simple
**Cons:** PC must stay on

---

### OPTION 2: Use GitHub Pages URLs (Best Long-term)
**For always-on solution:**

1. In SenseCraft, use **Web Content** feature (see your screenshot)
2. Enter URL: `https://tonicsouls.github.io/homehud/templates/isaac-words-random.json`
3. Device fetches from GitHub directly
4. No PC needed running
5. Updates when you push changes to GitHub

**URL Examples:**
```
https://tonicsouls.github.io/homehud/templates/isaac-words-random.json
https://tonicsouls.github.io/homehud/templates/rotating-quotes-2-updated.json
```

**Pros:** No PC needed, always available, clean
**Cons:** Updates only when you push to GitHub (not real-time)

---

### OPTION 3: Mix Both (Recommended)
**For flexibility:**

1. **Development:** Use `refresh-quotes.bat` locally while testing
2. **Production:** Push to GitHub, use URLs in SenseCraft
3. When you want new quotes/words:
   ```powershell
   python isaac_word_generator.py
   python dashboard_updater.py
   git add -A
   git commit -m "Update quotes and words"
   git push
   ```
4. SenseCraft fetches fresh templates from GitHub

---

## How to Use in SenseCraft

### Using Web Content (Your Screenshot shows this!)

1. Click "Web Content" in SenseCraft
2. Paste URL:
```
https://tonicsouls.github.io/homehud/templates/isaac-words-random.json
```
3. Click "Create Page"
4. SenseCraft will fetch and display the JSON

**Available template URLs:**

**For Isaac's Words:**
```
https://tonicsouls.github.io/homehud/templates/isaac-words-random.json
https://tonicsouls.github.io/homehud/templates/isaac-words-grade1.json
https://tonicsouls.github.io/homehud/templates/isaac-words-grade2.json
https://tonicsouls.github.io/homehud/templates/isaac-words-daily.json
```

**For Quotes:**
```
https://tonicsouls.github.io/homehud/templates/rotating-quotes-2-updated.json
https://tonicsouls.github.io/homehud/templates/rotating-quotes-4-updated.json
```

---

## Quick Action Items (Pick One Path)

### Path A: Local Testing (Quick Start)
```
1. Run: .\refresh-quotes.bat
2. Import template file locally into SenseCraft
3. Test with Isaac
4. Keep running while device is on
```

### Path B: GitHub Pages Only (Set & Forget)
```
1. In SenseCraft, click "Web Content"
2. Paste: https://tonicsouls.github.io/homehud/templates/isaac-words-random.json
3. Done! Device fetches from GitHub
4. To update: python script → git push → done
```

### Path C: Both (Flexible)
```
1. Use Local refresh during development
2. Push to GitHub for production
3. Use URLs in SenseCraft for final display
```

---

## The Bottom Line

**Your GitHub URLs are LIVE and READY to attach:**

✅ `https://tonicsouls.github.io/homehud/data/words/isaac-words.json`
✅ `https://tonicsouls.github.io/homehud/templates/isaac-words-random.json`
✅ `https://tonicsouls.github.io/homehud/templates/rotating-quotes-2-updated.json`

**You can:**
- Use them directly in SenseCraft (Web Content)
- Test locally with refresh-quotes.bat
- Mix both approaches

**Next steps:**
1. Choose your approach (A, B, or C)
2. Import template into SenseCraft
3. Test with device
4. Adjust as needed

---

## FAQ

**Q: Do I need refresh-quotes.bat?**
A: Only if you want real-time updates locally. GitHub URLs work without it.

**Q: Can I update words/quotes daily?**
A: Yes! Run scripts locally, git push, GitHub updates automatically.

**Q: Will links work forever?**
A: Yes, as long as the GitHub repo exists and is public.

**Q: Can SenseCraft fetch from GitHub URLs?**
A: Yes! Use "Web Content" feature to fetch live URLs.

**Q: What if I want daily updates automatically?**
A: GitHub Actions (advanced). For now, manual git push works great.

---

**Ready to test? Choose your path above and let me know what you pick!**
