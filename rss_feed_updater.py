#!/usr/bin/env python3
"""
RSS Feed Auto-Updater for Pokemon Beach News
Fetches latest articles and generates SenseCraft template
Designed to run periodically (every 30 mins - every hour)
"""

import json
import os
import feedparser
from datetime import datetime

class RSSFeedUpdater:
    """Fetch and format RSS feeds for SenseCraft"""
    
    def __init__(self, feed_url, output_dir, max_articles=4):
        self.feed_url = feed_url
        self.output_dir = output_dir
        self.max_articles = max_articles
        os.makedirs(output_dir, exist_ok=True)
    
    def fetch_feed(self):
        """Fetch and parse RSS feed"""
        try:
            print(f"📡 Fetching: {self.feed_url}")
            feed = feedparser.parse(self.feed_url)
            
            if feed.bozo:
                print(f"⚠️  Feed parse warning: {feed.bozo_exception}")
            
            articles = []
            for entry in feed.entries[:self.max_articles]:
                article = {
                    'title': entry.get('title', 'No title'),
                    'summary': entry.get('summary', '')[:200],  # Truncate to 200 chars
                    'link': entry.get('link', ''),
                    'published': entry.get('published', 'Unknown date')
                }
                articles.append(article)
            
            print(f"✓ Fetched {len(articles)} articles")
            return articles
        
        except Exception as e:
            print(f"❌ Error fetching feed: {e}")
            return []
    
    def generate_template(self, articles, template_name="pokemon-beach-news-updated.json"):
        """Generate SenseCraft template with articles"""
        
        if not articles:
            print("⚠️  No articles to display")
            return False
        
        # Build article text blocks
        article_text = "\n\n".join([
            f"📰 {a['title']}\n{a['summary']}"[:150]
            for a in articles[:3]
        ])
        
        template = {
            "stageElements": [
                {
                    "type": "text",
                    "x": 0,
                    "y": 0,
                    "width": 800,
                    "height": 50,
                    "fontSize": 28,
                    "fontWeight": "bold",
                    "color": "#FF6B9D",
                    "textAlign": "center",
                    "value": "🔥 POKEMON BEACH NEWS"
                },
                {
                    "type": "text",
                    "x": 20,
                    "y": 60,
                    "width": 760,
                    "height": 380,
                    "fontSize": 12,
                    "color": "#CCCCCC",
                    "textAlign": "left",
                    "value": article_text
                },
                {
                    "type": "text",
                    "x": 0,
                    "y": 450,
                    "width": 800,
                    "height": 30,
                    "fontSize": 10,
                    "color": "#666666",
                    "textAlign": "center",
                    "value": f"Updated: {datetime.now().strftime('%m/%d %H:%M')} | Source: Pikalytics Forum"
                }
            ],
            "container": {
                "width": 800,
                "height": 480,
                "background": "#000000"
            }
        }
        
        output_path = os.path.join(self.output_dir, template_name)
        with open(output_path, 'w') as f:
            json.dump(template, f, indent=2)
        
        print(f"✓ Saved: {output_path}")
        return True

if __name__ == '__main__':
    # Pokemon Beach RSS
    feed_url = "https://www.pokebeach.com/forums/forum/front-page-news.18/index.rss"
    output_dir = "templates"
    
    print("=" * 60)
    print("RSS Feed Auto-Updater")
    print("=" * 60)
    print()
    
    updater = RSSFeedUpdater(feed_url, output_dir)
    articles = updater.fetch_feed()
    
    if articles:
        updater.generate_template(articles, "pokemon-beach-news-updated.json")
        print()
        print("✓ RSS feed updated successfully!")
    else:
        print("❌ Failed to fetch articles")
    
    print()
    print("=" * 60)
