#!/usr/bin/env python3
"""
Generate static JSON files for GitHub Pages hosting
Creates a random quote snapshot that can be served as static content
"""

import json
import os
from datetime import datetime
from quote_rotator import QuoteRotator

def generate_github_pages_data():
    """Generate JSON files optimized for GitHub Pages serving"""
    
    quotes_dir = "quotes"
    data_dir = "data"
    
    # Ensure data directories exist
    os.makedirs(f"{data_dir}/quotes", exist_ok=True)
    os.makedirs(f"{data_dir}/templates", exist_ok=True)
    
    # Initialize rotator
    rotator = QuoteRotator(quotes_dir)
    rotator.load_quotes()
    
    print("=" * 60)
    print("GitHub Pages Data Generator")
    print("=" * 60)
    
    # Copy quote files to data directory
    for part in [1, 2, 3]:
        src = f"{quotes_dir}/quotes-part{part}.json"
        dst = f"{data_dir}/quotes/quotes-part{part}.json"
        if os.path.exists(src):
            with open(src, 'r') as f:
                data = json.load(f)
            with open(dst, 'w') as f:
                json.dump(data, f, indent=2)
            print(f"✓ Copied {src} → {dst}")
    
    # Generate random quote snapshot
    quotes = rotator.get_next_quotes(4)
    random_endpoint = {
        "timestamp": datetime.now().isoformat(),
        "quotes": quotes,
        "status": rotator.get_status(),
        "refresh_interval": "5 minutes"
    }
    
    with open(f"{data_dir}/quotes/random.json", 'w') as f:
        json.dump(random_endpoint, f, indent=2)
    print(f"✓ Generated random quote endpoint: {data_dir}/quotes/random.json")
    
    # Copy templates
    for template in ["rotating-quotes-2-updated", "rotating-quotes-4-updated"]:
        src = f"templates/quotes/{template}.json"
        dst = f"{data_dir}/templates/{template}.json"
        if os.path.exists(src):
            with open(src, 'r') as f:
                data = json.load(f)
            with open(dst, 'w') as f:
                json.dump(data, f, indent=2)
            print(f"✓ Copied {src} → {dst}")
    
    print("\n" + "=" * 60)
    print("GitHub Pages files ready in ./data/")
    print("=" * 60)
    print("\nNext steps:")
    print("1. Create a GitHub repository: homehud")
    print("2. Push these files to GitHub")
    print("3. Enable GitHub Pages (Settings → Pages)")
    print("4. Access data at: https://yourusername.github.io/homehud/data/")
    print("\nCURL examples:")
    print("  curl https://yourusername.github.io/homehud/data/quotes/random.json")
    print("  curl https://yourusername.github.io/homehud/data/quotes/quotes-part1.json")
    print("=" * 60)

if __name__ == '__main__':
    generate_github_pages_data()
