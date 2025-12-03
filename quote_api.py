#!/usr/bin/env python3
"""
Quote Rotation API - Returns non-repeating quote pairs
Tracks state using JSON file to ensure no duplicate pairs until full rotation
"""

import json
import os
from flask import Flask, jsonify
import csv
from datetime import datetime

app = Flask(__name__)

# File paths
STATE_FILE = "quote_state.json"
CSV_FILE = "wisdom12012025v1.csv"

# Configuration
QUOTES_PER_CALL = 2
REFRESH_INTERVAL_MIN = 5

def load_quotes_from_csv(csv_path):
    """Load quotes from CSV file"""
    quotes = []
    try:
        with open(csv_path, 'r', encoding='utf-8') as f:
            reader = csv.DictReader(f)
            for row in reader:
                quotes.append({
                    "author": row.get("Author", "Unknown"),
                    "message": row.get("Message", ""),
                    "category": row.get("Category", ""),
                    "insight": row.get("Insight", "")
                })
    except FileNotFoundError:
        print(f"CSV file not found: {csv_path}")
    return quotes

def load_state():
    """Load rotation state from JSON file"""
    if os.path.exists(STATE_FILE):
        try:
            with open(STATE_FILE, 'r') as f:
                return json.load(f)
        except:
            pass
    
    # Initialize fresh state
    quotes = load_quotes_from_csv(CSV_FILE)
    return {
        "all_quotes": quotes,
        "current_index": 0,
        "shown_pairs": [],
        "rotation_complete": False,
        "last_refresh": datetime.now().isoformat(),
        "total_quotes": len(quotes)
    }

def save_state(state):
    """Save rotation state to JSON file"""
    state["last_refresh"] = datetime.now().isoformat()
    with open(STATE_FILE, 'w') as f:
        json.dump(state, f, indent=2)

def get_next_pair(state):
    """
    Get next pair of quotes ensuring:
    1. No duplicate pairs until full rotation
    2. No same quote twice in a row within pair
    """
    quotes = state["all_quotes"]
    total = len(quotes)
    current_idx = state["current_index"]
    
    if total < QUOTES_PER_CALL:
        return None  # Not enough quotes
    
    # Check if we've completed a rotation
    if state["rotation_complete"]:
        state["shown_pairs"] = []
        state["rotation_complete"] = False
    
    # Get two quotes without repeating within the pair
    pair = []
    idx = current_idx
    
    for _ in range(QUOTES_PER_CALL):
        pair.append({
            "quote": quotes[idx % total]["message"],
            "author": quotes[idx % total]["author"],
            "category": quotes[idx % total]["category"],
            "insight": quotes[idx % total]["insight"]
        })
        idx = (idx + 1) % total
    
    # Store this pair
    state["shown_pairs"].append({
        "indices": [current_idx, (current_idx + 1) % total],
        "timestamp": datetime.now().isoformat()
    })
    
    # Update index for next call
    state["current_index"] = (current_idx + QUOTES_PER_CALL) % total
    
    # Check if rotation complete (roughly after cycling through)
    if state["current_index"] < QUOTES_PER_CALL:
        state["rotation_complete"] = True
    
    return pair

@app.route('/api/quotes/next', methods=['GET'])
def get_next_quotes():
    """API endpoint to get next quote pair"""
    state = load_state()
    pair = get_next_pair(state)
    
    if not pair:
        return jsonify({"error": "Not enough quotes"}), 400
    
    save_state(state)
    
    return jsonify({
        "quotes": pair,
        "call_number": len(state["shown_pairs"]),
        "rotation_progress": f"{len(state['shown_pairs'])} / {state['total_quotes'] // QUOTES_PER_CALL}",
        "rotation_complete": state["rotation_complete"],
        "refresh_interval_minutes": REFRESH_INTERVAL_MIN,
        "timestamp": datetime.now().isoformat()
    })

@app.route('/api/quotes/status', methods=['GET'])
def get_status():
    """API endpoint to check rotation status"""
    state = load_state()
    return jsonify({
        "total_quotes": state["total_quotes"],
        "pairs_shown": len(state["shown_pairs"]),
        "current_index": state["current_index"],
        "rotation_complete": state["rotation_complete"],
        "estimated_cycle_time_hours": (state["total_quotes"] // QUOTES_PER_CALL * REFRESH_INTERVAL_MIN) / 60
    })

@app.route('/api/quotes/reset', methods=['POST'])
def reset_rotation():
    """Reset rotation counter (admin endpoint)"""
    quotes = load_quotes_from_csv(CSV_FILE)
    state = {
        "all_quotes": quotes,
        "current_index": 0,
        "shown_pairs": [],
        "rotation_complete": False,
        "last_refresh": datetime.now().isoformat(),
        "total_quotes": len(quotes)
    }
    save_state(state)
    return jsonify({"message": "Rotation reset", "total_quotes": len(quotes)})

if __name__ == '__main__':
    # Load CSV on startup
    print(f"Loading quotes from {CSV_FILE}...")
    state = load_state()
    print(f"Loaded {state['total_quotes']} quotes")
    print(f"Will show {QUOTES_PER_CALL} quotes every {REFRESH_INTERVAL_MIN} minutes")
    print(f"Estimated cycle time: {(state['total_quotes'] // QUOTES_PER_CALL * REFRESH_INTERVAL_MIN) / 60:.1f} hours")
    
    # Run Flask app
    app.run(host='0.0.0.0', port=5000, debug=False)
