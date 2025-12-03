# SAVEPOINT: HOMEHUD Modular Restructure

Date: 2025-12-03

What is included in this savepoint:
- Modular directories created: `isaac-words/` and `pokemon-news/`
- All SenseCraft template JSONs moved / recreated in each module's `templates/`
- `data/` and `index.html` documentation pages created for each module
- Batch scripts added for auto-update and GitHub push:
  - `refresh-isaac-words-with-push.bat`
  - `refresh-rss-feeds-with-push.bat`
- RSS updater and isaac_word_generator scripts exist and are tested.
- Git commits pushed to `main` and Docs created (README_MODULAR.md, MODULAR_STRUCTURE.md, SETUP_GUIDE_MODULAR.md)

Git commit ids at time of savepoint:
- c3fcd28  (improved batch scripts with GitHub auto-push; update RSS feed timestamp)
- ef8a314  (modular README)
- d7dab92  (modular structure documentation)
- b62edcc  (initial modular restructure)

Tagging recommendation: `savepoint/modular/2025-12-03`

Next steps (if you continue work on another machine):
1. Clone the repo or use the new module directories.
2. Ensure each module's `templates/` URLs are the ones you add to SenseCraft HMI.
3. If you want each module in its own repo, see `INTENT_REPOS_DYNAMIC.md` for proposed steps.

Notes:
- The `rss_feed_updater.py` and `isaac_word_generator.py` are available and can be run manually in the repo root.
- If you plan to run auto-update scripts on a server/CI, migrate batch logic to GitHub Actions (example provided).
