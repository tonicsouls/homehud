#!/usr/bin/env python3
"""
Isaac's Word of the Day Generator
Picks random words from the word list and populates SenseCraft template
For 7-year-old learning 1st and 2nd grade vocabulary with emojis
"""

import json
import os
import random
from datetime import datetime

class IsaacWordGenerator:
    """Generate daily vocabulary for Isaac"""
    
    def __init__(self, words_file, template_file, output_dir):
        self.words_file = words_file
        self.template_file = template_file
        self.output_dir = output_dir
        self.words = []
        self.load_words()
    
    def load_words(self):
        """Load word list from JSON"""
        try:
            with open(self.words_file, 'r', encoding='utf-8') as f:
                data = json.load(f)
                self.words = data.get('words', [])
                print(f"✓ Loaded {len(self.words)} words")
        except FileNotFoundError:
            print(f"❌ Word file not found: {self.words_file}")
            return False
        return True
    
    def get_random_word(self, grade=None):
        """Get a random word, optionally filtered by grade"""
        if grade:
            filtered = [w for w in self.words if w.get('grade') == grade]
            if filtered:
                return random.choice(filtered)
        return random.choice(self.words)
    
    def get_word_by_day(self, day_of_year=None):
        """Get sequential word based on day of year (for future daily tracking)"""
        if day_of_year is None:
            day_of_year = datetime.now().timetuple().tm_yday
        
        # Cycle through words if day exceeds total words
        word_index = (day_of_year - 1) % len(self.words)
        return self.words[word_index]
    
    def generate_template(self, word=None, output_file=None):
        """Generate populated template with word data"""
        
        # Pick random word if none provided
        if word is None:
            word = self.get_random_word()
        
        # Load template
        try:
            with open(self.template_file, 'r', encoding='utf-8') as f:
                template = json.load(f)
        except FileNotFoundError:
            print(f"❌ Template file not found: {self.template_file}")
            return False
        
        # Update template elements
        for elem in template.get('elements', []):
            if elem.get('id') == 'emoji':
                elem['value'] = word.get('emoji', '📝')
            elif elem.get('id') == 'word':
                elem['value'] = word.get('word', 'Word')
            elif elem.get('id') == 'definition':
                elem['value'] = word.get('definition', 'Definition')
            elif elem.get('id') == 'example':
                elem['value'] = f"Example: {word.get('example', 'Example sentence')}"
            elif elem.get('id') == 'footer':
                grade = word.get('grade', 1)
                category = word.get('category', 'Learning')
                elem['value'] = f"Grade {grade} | {category}"
        
        # Save output
        if output_file is None:
            output_file = os.path.join(self.output_dir, 'isaac-words-updated.json')
        
        os.makedirs(self.output_dir, exist_ok=True)
        
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(template, f, indent=2)
        
        return True
    
    def generate_all_variants(self):
        """Generate 3 versions: random, grade1 only, grade2 only"""
        
        results = {}
        
        # Random word
        word = self.get_random_word()
        if self.generate_template(word, os.path.join(self.output_dir, 'isaac-words-random.json')):
            results['random'] = f"Random: {word['word']}"
        
        # Grade 1 word
        word_g1 = self.get_random_word(grade=1)
        if self.generate_template(word_g1, os.path.join(self.output_dir, 'isaac-words-grade1.json')):
            results['grade1'] = f"Grade 1: {word_g1['word']}"
        
        # Grade 2 word
        word_g2 = self.get_random_word(grade=2)
        if self.generate_template(word_g2, os.path.join(self.output_dir, 'isaac-words-grade2.json')):
            results['grade2'] = f"Grade 2: {word_g2['word']}"
        
        # Sequential (day-based)
        word_seq = self.get_word_by_day()
        if self.generate_template(word_seq, os.path.join(self.output_dir, 'isaac-words-daily.json')):
            results['daily'] = f"Today's Word: {word_seq['word']}"
        
        return results

if __name__ == '__main__':
    import sys
    
    # Define paths
    base_dir = os.path.dirname(__file__)
    words_file = os.path.join(base_dir, 'data', 'words', 'isaac-words.json')
    template_file = os.path.join(base_dir, 'templates', 'isaac-words-template.json')
    output_dir = os.path.join(base_dir, 'templates')
    
    print("=" * 60)
    print("Isaac's Word Generator")
    print("=" * 60)
    print()
    
    generator = IsaacWordGenerator(words_file, template_file, output_dir)
    
    # Generate all variants
    results = generator.generate_all_variants()
    
    print("✓ Generated templates:")
    for key, value in results.items():
        print(f"  • {value}")
    
    print()
    print("=" * 60)
    print("Templates updated!")
    print("=" * 60)
    print()
    print("Files created:")
    print("  • isaac-words-random.json  - Random word each time")
    print("  • isaac-words-grade1.json  - Grade 1 words only")
    print("  • isaac-words-grade2.json  - Grade 2 words only")
    print("  • isaac-words-daily.json   - Sequential daily word")
    print()
    print("Import any of these into SenseCraft for Isaac's display!")
    print()
