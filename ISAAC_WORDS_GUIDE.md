# Isaac's Word Learning System 📚✏️

## Overview
A daily vocabulary builder for 7-year-old Isaac with:
- **30 starter words** (Grades 1-2)
- **Emojis** to help identify and remember words
- **Definitions** in kid-friendly language
- **Example sentences** showing how to use the word
- **Categories** (Animals, Food, Nature, etc.)
- **4 display modes** (Random, Grade 1 only, Grade 2 only, Sequential daily)

---

## Word List (30 Words)

### Grade 1 (20 Words - Basic Vocabulary)
| # | Word | Emoji | Category |
|---|------|-------|----------|
| 1 | Apple | 🍎 | Food |
| 2 | Ball | ⚽ | Toys |
| 3 | Cat | 🐱 | Animals |
| 4 | Dog | 🐕 | Animals |
| 5 | Egg | 🥚 | Food |
| 6 | Fish | 🐟 | Animals |
| 7 | Garden | 🌻 | Places |
| 8 | House | 🏠 | Places |
| 9 | Ice | ❄️ | Nature |
| 10 | Jump | 🦘 | Actions |
| 11 | Kite | 🪁 | Toys |
| 12 | Lion | 🦁 | Animals |
| 13 | Moon | 🌙 | Sky |
| 14 | Nest | 🪶 | Nature |
| 15 | Orange | 🍊 | Food |
| 16 | Pig | 🐷 | Animals |
| 17 | Queen | 👑 | People |
| 18 | Rainbow | 🌈 | Sky |
| 19 | Star | ⭐ | Sky |
| 20 | Tree | 🌳 | Nature |

### Grade 2 (10 Words - More Complex)
| # | Word | Emoji | Category |
|---|------|-------|----------|
| 21 | Adventure | 🗺️ | Actions |
| 22 | Bicycle | 🚲 | Vehicles |
| 23 | Butterfly | 🦋 | Insects |
| 24 | Camera | 📷 | Tools |
| 25 | Dinosaur | 🦕 | Animals |
| 26 | Elephant | 🐘 | Animals |
| 27 | Friendship | 🤝 | People |
| 28 | Giraffe | 🦒 | Animals |
| 29 | Horizon | 🌅 | Sky |
| 30 | Island | 🏝️ | Places |

---

## Display Modes

### 1. **Random** (Recommended for Fun)
```
isaac-words-random.json
```
- Shows a random word each time
- No repeat patterns
- Great for: Daily refreshes, keeping it interesting

**Use when:** You want Isaac to see a surprise word every refresh

---

### 2. **Grade 1 Only** (For Learning Foundations)
```
isaac-words-grade1.json
```
- Only shows Grade 1 (easier) words
- Perfect for: Building confidence, learning fundamentals

**Use when:** Starting Isaac on vocabulary learning

---

### 3. **Grade 2 Only** (For Challenge)
```
isaac-words-grade2.json
```
- Only shows Grade 2 (harder) words
- Perfect for: Advancing after Grade 1 mastery

**Use when:** Isaac is ready for more challenging words

---

### 4. **Daily Sequential** (For Structured Learning)
```
isaac-words-daily.json
```
- Same word all day (changes at midnight)
- Repeats every 30 days
- Perfect for: Structured daily learning, tracking progress

**Use when:** You want a predictable, sequential curriculum

---

## Templates

### Main Template
**File:** `templates/isaac-words-template.json`

**Layout:**
```
┌─────────────────────────────────┐
│  ✏️ ISAAC'S WORD OF THE DAY    │
│                        12/02/2025│
├─────────────────────────────────┤
│                                 │
│              🍎                 │
│                                 │
│            APPLE                │
│  A red or green fruit...        │
│  Example: I eat an apple...     │
│                                 │
│    Grade 1 | Category: Food     │
│                                 │
├─────────────────────────────────┤
│  Learn one new word every day! 📚│
└─────────────────────────────────┘
```

**Design Features:**
- Large emoji for visual identification
- Big word text (36pt, bright green)
- Simple definition (kid-friendly)
- Example sentence showing real usage
- Grade level and category info
- Dark background with green accents

---

## Usage Instructions

### Option A: Auto-Refresh Every 5 Minutes
```powershell
# Create a batch file that runs the generator periodically
# Use Windows Task Scheduler
# Run: isaac_word_generator.py every 5 minutes
```

**Step-by-step:**
1. Open Task Scheduler (search in Windows)
2. Create Basic Task
3. Name: "Isaac Word Refresh"
4. Trigger: Every 5 minutes
5. Action: Run `python isaac_word_generator.py`
6. Location: `C:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD`

---

### Option B: Manual Refresh
```powershell
cd "C:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD"
python isaac_word_generator.py
```

This will regenerate all 4 template variants with new random words.

---

### Option C: Daily Refresh Only
```bash
# GitHub Actions (auto-updates daily at midnight)
# Coming soon - will auto-update isaac-words-daily.json
```

---

## Scaling Up (Future)

### Add More Words
1. Edit `data/words/isaac-words.json`
2. Add new entries with emoji, definition, example
3. Increase `grade_1_words` and `grade_2_words` count
4. Run `isaac_word_generator.py`
5. Push to GitHub

**Suggested expansions:**
- Full alphabet (A-Z = 26+ words per grade = 52+ total)
- Seasonal words (spring flowers, winter snow, etc.)
- Thematic words (dinosaurs, space, ocean, jungle)
- Interactive tracking (mark learned words)

---

## Integration with SenseCraft

1. **Import Template**
   - SenseCraft → Import Dashboard
   - Select `isaac-words-random.json` (or your preferred variant)

2. **Set Refresh**
   - Configure device to refresh every 5 minutes
   - Or manually refresh when you run the generator

3. **Display on Device**
   - Template will show on reTerminal E1001
   - Large emoji + word + definition visible
   - Grade level helps you track progress

---

## Example Output

**When run, generates:**
```
isaac-words-random.json    → "🐱 Cat - A small animal with whiskers"
isaac-words-grade1.json    → "👑 Queen - A woman who rules a kingdom"
isaac-words-grade2.json    → "🦋 Butterfly - A colorful insect with big wings"
isaac-words-daily.json     → "🐟 Fish - An animal that lives in water" (same all day)
```

Each file is ready to import into SenseCraft immediately.

---

## Data Files

```
data/words/
├── isaac-words.json           ← Master word list (30 words)
└── metadata                   ← Categories, grades, counts

templates/
├── isaac-words-template.json  ← Base template
├── isaac-words-random.json    ← Generated: Random word
├── isaac-words-grade1.json    ← Generated: Grade 1 only
├── isaac-words-grade2.json    ← Generated: Grade 2 only
└── isaac-words-daily.json     ← Generated: Sequential daily
```

---

## Tips for Success

1. **Start Simple:** Use "Random" mode to keep it fun
2. **Emoji Help:** The emoji is the main identifier for 7-year-olds
3. **Read Aloud:** Read definition + example together
4. **Celebrate:** Make word learning a daily fun ritual
5. **Track Progress:** Note which words he's learned and mastered
6. **Expand Gradually:** Add 5-10 new words per week as he progresses

---

## Example Session

**Mom/Dad:** "Hey Isaac! Let's see today's word!"
📱 *Device shows:*
```
      🍎
     APPLE
  A red or green fruit 
  that grows on trees
  
  Example: I eat an apple 
  for a healthy snack
```

**Isaac:** "I know this one! Can we have an apple after lunch?"

**You:** "Perfect! You learned the word 'apple'! ✓ Let's see a new one tomorrow!"

---

**Files:** All files committed to GitHub
**Status:** Ready to deploy! 🚀
**Next:** Import into SenseCraft and test with Isaac!

---

Questions? Check `DYNAMIC_CONTENT.md` for info on how to make this truly dynamic with GitHub Actions!
