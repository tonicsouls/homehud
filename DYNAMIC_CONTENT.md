# Dynamic GitHub Pages Solutions

## The Challenge
GitHub Pages serves static files (HTML, JSON, CSS). When you fetch `quotes.json`, you get the same file forever until you push a new version.

## Solutions for "Dynamic" Content

### Option 1: GitHub Actions (BEST FOR YOUR CASE) ✅
**How it works:**
- Scheduled job runs on GitHub servers (no PC needed)
- Script updates JSON files automatically
- Pushes changes back to repo
- Website automatically serves new data

**Example schedule:** Every 5 minutes, every day, etc.

**Pros:**
- ✅ Truly dynamic (real updates)
- ✅ No PC running 24/7
- ✅ Free tier includes 2,000 minutes/month
- ✅ Works for quotes, words, any JSON

**Cons:**
- ❌ Small delay (5-10 mins for update cycle)
- ❌ Slightly more complex setup

**Build time:** 1 hour

---

### Option 2: Client-Side Randomization (EASIEST) ⚡
**How it works:**
- Upload all 365 words to GitHub
- Device/browser picks random word on load
- Each refresh = different word (instant!)

**Pros:**
- ✅ Instant randomization
- ✅ No server needed
- ✅ Simple to set up (10 mins)
- ✅ No GitHub Actions complexity

**Cons:**
- ❌ Not truly sequential (might repeat same word)
- ❌ Needs device-side logic

**Best for:** Isaac (simple, instant, playful)

---

### Option 3: Netlify Functions (ADVANCED)
**How it works:**
- Deploy to Netlify instead of GitHub Pages
- Run serverless functions
- Returns different data on each call

**Pros:**
- ✅ True server-side dynamic logic
- ✅ Can track state (word #47 of year)
- ✅ Powerful

**Cons:**
- ❌ More complex setup
- ❌ Requires Netlify account
- ❌ Overkill for your needs

**Build time:** 2-3 hours

---

## Recommendation for Isaac

**Use Option 2 (Client-Side Randomization):**
- Upload 365 words as JSON
- Each device refresh picks random word + emoji
- Instant, fun, no delays
- If he learns a word, check it off (tracked locally)

Later, upgrade to **Option 1 (GitHub Actions)** for sequential daily words.

---

## Quick Comparison

| Feature | Option 1 | Option 2 | Option 3 |
|---------|----------|----------|----------|
| Dynamic | ✅ Yes | ⚡ Pseudo | ✅✅ Yes |
| Free | ✅ Yes | ✅ Yes | ✅ Free tier |
| Setup Time | 1 hr | 10 min | 2-3 hrs |
| Complexity | Medium | Low | High |
| Best For | Quotes | Words | Complex Apps |

**I recommend: Start with Option 2 (quick & fun), upgrade to Option 1 later (sequential learning)**
