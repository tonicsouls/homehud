# INTENT: Modular Repos + Dynamic Hosting Updates

Overview
--------
This document discusses a deployment strategy where each module of the HOMEHUD project (e.g., Isaac's Words, Pokemon News) lives in its own GitHub repository. Each repo is autonomous: it contains its own templates, data, and automation (GitHub Actions) that fetch or generate refreshed content and push to its own GitHub Pages site. The reTerminal E1001 (SenseCraft) only has to point at the hosted JSON URL — no device-side execution required.

Why separate repos?
-------------------
- Isolation: Changes to one module do not affect others.
- Ownership: Different teams or processes can manage modules separately.
- CI/Automation: Each repo has its own GitHub Action workflows with tailored schedules and secrets.
- Security: Minimize credentials exposure; PATs only need limited scope.
- People-friendly: Each module can include documentation and independent update cycles.

Flow and Responsibilities
-------------------------
1. Module repo stores:
   - `templates/` — final SenseCraft JSON files generated or updated
   - `data/` — master data JSON or CSV (e.g., `isaac-words.json`)
   - `scripts/` — python scripts that read `data/`, generate templates
   - Optional: `scrapers/` — scripts that pull content (e.g., web scraper for Pokemon forums)
   - `docs/` — module usage instructions
2. Automation (GitHub Actions):
   - Scheduled runs (CRON) or webhooks triggering scrapers/fetchers
   - Script run: fetch RSS / scrape pages / generate templates
   - Commit and push templates to `templates/` folder
   - GitHub Pages hosts the `templates/` directory (GitHub Pages build or raw content path)
3. SenseCraft: Add the hosted URL from that module repo to the Web Content feature.

Question: "Can I have an updated environment where GitHub pulls in new information?"
-------------------------------------------------------------------------------
- Yes. GitHub Actions can run scheduled workflows or respond to webhooks.
- A scheduled Action can call RSS parsers, scrapers, or APIs; generate content; and commit back to the repo.
- GitHub Pages will then serve the updated JSON files; SenseCraft will fetch the updated JSON and re-render.

Design: Basic Example for a Module (Pokemon News)
-------------------------------------------------
- `repository`: `tonicsouls/pokemon-news` (GitHub Pages site enabled via `gh-pages` or `main` branch pages)
- Files:
  - `templates/pokemon-beach-news-updated.json` — final template served to SenseCraft
  - `scripts/rss_feed_updater.py` — fetches Pokemon Beach docs
  - `.github/workflows/auto-update.yml` — cron-based 30-min update & commit

Simplified GitHub Actions Example (auto-update.yml)
--------------------------------------------------
```yaml
name: Auto Update - Pokemon News
on:
  schedule:
    - cron: '*/30 * * * *'
  workflow_dispatch:

jobs:
  update:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Setup Python
        uses: actions/setup-python@v4
        with:
          python-version: '3.10'

      - name: Install dependencies
        run: pip install -r requirements.txt

      - name: Run RSS updater
        run: python scripts/rss_feed_updater.py

      - name: Commit and push changes
        run: |
          git config user.email "action@github.com"
          git config user.name "GitHub Actions"
          git add templates/pokemon-beach-news-updated.json
          git commit -m "Auto-update: pokemon-beach-news-updated.json [ci skip]" || echo "No changes"
          git push
        env:
          # Set PERSONAL_ACCESS_TOKEN in repo secrets to push to GitHub when using protected branches
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

Security / Token Management
---------------------------
- Use the built-in `GITHUB_TOKEN` or a PAT with `repo` scope if writing to a protected branch.
- Keep scraping/sensitive credentials in GitHub repository Secrets; do not commit API keys to repo.
- If you need cross-repo access (push to a different repo), a PAT with limited scopes can be stored as a secret.

Operational Notes
-----------------
- If you plan to keep multiple repos auto-updating, create a shared `common-scripts` repo or an Action template for reuse.
- Logging: Include a `log/` folder or push timestamps to `metadata` in JSON (i.e., `{"last_updated": "2025-12-03T05:51Z"}`).
- Rate-limits: Respect site scraping policies and throttle access to avoid being blocked.
- Error handling: GitHub Actions should log failures and optionally open PR or issue when the run fails repeatedly.

Is this feasible? — Short Answer
-------------------------------
Yes. GitHub Actions or any CI triggered by schedule/webhook can fetch new data, generate templates, and push them to GitHub Pages, meaning the display device only pulls the hosted template URL and never needs to run an update script locally.

Recommendations
---------------
- Start with two repos:
  1. `tonicsouls/isaac-words` — daily words generator & templates
  2. `tonicsouls/pokemon-news` — RSS updates & templates
- Add Action workflows similar to the example above with appropriate schedule.
- Optional: Add a small status endpoint (or GitHub Pages status page) to quickly confirm last update times.

Next steps if you want to proceed
--------------------------------
1. Decide which modules to split into separate repos.
2. Create new GitHub repositories, copy files, and set up GitHub Pages for each.
3. Add workflow file and Secrets (if needed).
4. Verify workflows by running `workflow_dispatch` and checking GitHub Pages content.

--
Generated: 2025-12-03
