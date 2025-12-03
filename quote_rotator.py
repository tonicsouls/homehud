#!/usr/bin/env python3
"""
Quote Rotation Manager - Loads local JSON files and manages rotating quote display
Ensures no duplicates until full cycle, randomly selects 3-4 quotes per rotation
"""

import json
import random
import os
from pathlib import Path
from datetime import datetime

class QuoteRotator:
    def __init__(self, quotes_dir="quotes"):
        """Initialize with quotes directory"""
        self.quotes_dir = quotes_dir
        self.all_quotes = []
        self.shown_indices = []
        self.current_rotation = 0
        self.total_rotations = 0
        
        # Load all quotes from JSON files
        self.load_quotes()
        
    def load_quotes(self):
        """Load all quotes from JSON files in quotes directory"""
        quotes_path = Path(self.quotes_dir)
        
        # Sort files to load in order (part1, part2, part3)
        json_files = sorted(quotes_path.glob("quotes-part*.json"))
        
        for json_file in json_files:
            try:
                with open(json_file, 'r', encoding='utf-8') as f:
                    data = json.load(f)
                    self.all_quotes.extend(data.get("quotes", []))
                    print(f"Loaded {len(data.get('quotes', []))} quotes from {json_file.name}")
            except Exception as e:
                print(f"Error loading {json_file}: {e}")
        
        print(f"Total quotes loaded: {len(self.all_quotes)}")
        self.total_rotations = len(self.all_quotes)
    
    def get_next_quotes(self, count=3):
        """
        Get next 3-4 random quotes without duplicates until full rotation
        
        Args:
            count: 3 or 4 quotes (default 3)
        
        Returns:
            List of quote dictionaries
        """
        if not self.all_quotes:
            return []
        
        # If we've shown all quotes, reset for new rotation
        if len(self.shown_indices) >= len(self.all_quotes):
            self.shown_indices = []
            self.current_rotation += 1
            print(f"Rotation complete! Starting rotation {self.current_rotation + 1}")
        
        # Get available indices (not yet shown in this rotation)
        available = [i for i in range(len(self.all_quotes)) if i not in self.shown_indices]
        
        # Randomly select count quotes
        count = min(count, len(available))  # Don't exceed available quotes
        selected_indices = random.sample(available, count)
        
        # Mark as shown
        self.shown_indices.extend(selected_indices)
        
        # Get the actual quotes
        selected_quotes = [self.all_quotes[i] for i in selected_indices]
        
        return selected_quotes
    
    def get_status(self):
        """Return status of rotation"""
        return {
            "total_quotes": len(self.all_quotes),
            "shown_in_rotation": len(self.shown_indices),
            "rotation_number": self.current_rotation + 1,
            "progress_percent": (len(self.shown_indices) / len(self.all_quotes) * 100) if self.all_quotes else 0
        }
    
    def reset_rotation(self):
        """Reset rotation counter"""
        self.shown_indices = []
        self.current_rotation = 0
        print("Rotation reset")

# Example usage for testing
if __name__ == "__main__":
    rotator = QuoteRotator("quotes")
    
    print("\n=== Quote Rotator Demo ===\n")
    
    # Get 5 sets of quotes to see rotation
    for i in range(5):
        print(f"\n--- Fetch #{i+1} ---")
        quotes = rotator.get_next_quotes(count=3)
        
        for q in quotes:
            print(f"\n{q['author']}")
            print(f"  \"{q['message']}\"")
            print(f"  💡 {q['insight']}")
        
        status = rotator.get_status()
        print(f"\nStatus: {status['shown_in_rotation']}/{status['total_quotes']} shown ({status['progress_percent']:.1f}%)")
