# SenseCraft Dashboard Templates

This folder contains reusable SenseCraft dashboard templates organized by content type.

## Structure

```
templates/
├── quotes/              # Daily wisdom rotating quotes
├── news-feeds/          # RSS feed dashboards (Hacker News, Pokemon, etc)
├── weather/             # Weather displays
├── calendar/            # Calendar & events
└── productivity/        # Tasks, todos, progress trackers
```

## Quote Templates

- **rotating-quotes-4.json** - 4 quote grid (2x2 layout)
- **rotating-quotes-2.json** - 2 quotes (1 featured, 1 secondary)

### How to use rotating quotes:

1. Place quotes JSON files in the `quotes/` folder
2. Run `quote_rotator.py` to cycle through quotes
3. Import the template into SenseCraft
4. Update text elements with rotating quote data

## To Add Your Own Template

1. Copy an existing template
2. Modify element positions and sizes
3. Save with descriptive name
4. Update this README

---

**Last Updated:** December 2, 2025
