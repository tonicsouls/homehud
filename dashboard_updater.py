#!/usr/bin/env python3
"""
Quote & RSS Feed Manager for SenseCraft Dashboard
Fetches quotes from local JSON and populates SenseCraft templates
"""

import json
import os
from datetime import datetime
from quote_rotator import QuoteRotator

class DashboardUpdater:
    """Updates SenseCraft dashboard templates with live data"""
    
    def __init__(self, template_dir, quotes_dir):
        self.template_dir = template_dir
        self.quotes_dir = quotes_dir
        self.rotator = QuoteRotator(quotes_dir)
        self.rotator.load_quotes()
    
    def update_rotating_quotes_2(self, output_path=None):
        """Update the 2-quote template with fresh quotes"""
        quotes = self.rotator.get_next_quotes(2)
        
        # Load template
        template_path = os.path.join(self.template_dir, 'rotating-quotes-2.json')
        with open(template_path, 'r') as f:
            template = json.load(f)
        
        # Update elements with real quote data
        for elem in template['elements']:
            # Update first quote
            if elem['id'] == 'author-1':
                elem['value'] = quotes[0]['author']
            elif elem['id'] == 'quote-text-1':
                elem['value'] = quotes[0]['message']
            elif elem['id'] == 'insight-1':
                elem['value'] = quotes[0]['insight']
            
            # Update second quote
            elif elem['id'] == 'author-2':
                elem['value'] = quotes[1]['author']
            elif elem['id'] == 'quote-text-2':
                elem['value'] = quotes[1]['message']
            
            # Update footer with rotation status
            elif elem['id'] == 'footer':
                status = self.rotator.get_status()
                elem['value'] = f"Rotation {status['rotation_number']} • {status['progress_percent']:.0f}% through cycle"
        
        # Save updated template
        output = output_path or os.path.join(self.template_dir, 'rotating-quotes-2-updated.json')
        with open(output, 'w') as f:
            json.dump(template, f, indent=2)
        
        print(f"✓ Updated 2-quote template: {output}")
        return output
    
    def update_rotating_quotes_4(self, output_path=None):
        """Update the 4-quote template with fresh quotes"""
        quotes = self.rotator.get_next_quotes(4)
        
        # Load template
        template_path = os.path.join(self.template_dir, 'rotating-quotes-4.json')
        with open(template_path, 'r') as f:
            template = json.load(f)
        
        # Update elements with real quote data
        for elem in template['elements']:
            # Update each quote (1-4)
            for i in range(1, 5):
                if elem['id'] == f'author-{i}':
                    elem['value'] = quotes[i-1]['author']
                elif elem['id'] == f'quote-text-{i}':
                    elem['value'] = quotes[i-1]['message']
                elif elem['id'] == f'insight-{i}':
                    elem['value'] = quotes[i-1]['insight']
            
            # Update footer
            if elem['id'] == 'footer':
                status = self.rotator.get_status()
                elem['value'] = f"Rotation {status['rotation_number']} • {status['progress_percent']:.0f}% through cycle"
        
        # Save updated template
        output = output_path or os.path.join(self.template_dir, 'rotating-quotes-4-updated.json')
        with open(output, 'w') as f:
            json.dump(template, f, indent=2)
        
        print(f"✓ Updated 4-quote template: {output}")
        return output

if __name__ == '__main__':
    # Define paths
    base_dir = os.path.dirname(__file__)
    template_dir = os.path.join(base_dir, 'templates', 'quotes')
    quotes_dir = os.path.join(base_dir, 'quotes')
    
    # Create updater and generate templates
    updater = DashboardUpdater(template_dir, quotes_dir)
    
    print("=" * 60)
    print("Dashboard Template Updater")
    print("=" * 60)
    
    # Update both templates
    updater.update_rotating_quotes_2()
    updater.update_rotating_quotes_4()
    
    print("\nTemplates updated! Import the *-updated.json files into SenseCraft.")
    print("Run this script again before each device refresh to get new quotes.")
