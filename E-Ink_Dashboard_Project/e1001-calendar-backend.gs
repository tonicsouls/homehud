/**
 * E1001 Calendar Display - Backend API
 * Deploy this as a Google Apps Script Web App
 * 
 * Setup Instructions:
 * 1. Go to script.google.com
 * 2. Paste this code
 * 3. Click "Services" (+) and add "Google Tasks API"
 * 4. Deploy > New Deployment > Web App
 * 5. Set access to "Anyone"
 * 6. Copy the web app URL for your device
 */

function doGet(e) {
  var today = new Date();
  var tomorrow = new Date(today);
  tomorrow.setDate(tomorrow.getDate() + 1);
  
  // Fetch next calendar event
  var calendarId = 'primary';
  var events = CalendarApp.getCalendarById(calendarId).getEvents(today, tomorrow);
  var nextEvent = events.length > 0 ? {
    title: events[0].getTitle(),
    time: Utilities.formatDate(events[0].getStartTime(), Session.getScriptTimeZone(), "h:mm a"),
    location: events[0].getLocation() || ""
  } : { 
    title: "No events scheduled", 
    time: "", 
    location: "" 
  };
  
  // Fetch Google Tasks (top 3 due today or overdue)
  var taskLists = Tasks.Tasklists.list().items;
  var todos = [];
  
  if (taskLists && taskLists.length > 0) {
    var taskListId = taskLists[0].id;
    var tasks = Tasks.Tasks.list(taskListId, {
      showCompleted: false,
      maxResults: 5
    });
    
    if (tasks.items) {
      for (var i = 0; i < Math.min(3, tasks.items.length); i++) {
        todos.push(tasks.items[i].title);
      }
    }
  }
  
  // Calculate Isaac's Aligner Progress
  // Start: Oct 21, 2025 | Duration: 730 days (2 years)
  var alignerStart = new Date("2025-10-21");
  var diffTime = today - alignerStart;
  var diffDays = Math.max(0, Math.ceil(diffTime / (1000 * 60 * 60 * 24)));
  var totalDays = 730;
  var percentComplete = Math.min(100, Math.floor((diffDays / totalDays) * 100));
  
  // Determine next change day (every Tuesday)
  var daysUntilTuesday = (2 - today.getDay() + 7) % 7 || 7;
  
  // Get weather for Keller, TX (you'll need to add API key for real weather)
  // For now, using placeholder - consider OpenWeatherMap free tier
  var weather = {
    temp: "68°F",
    condition: "Partly Cloudy",
    aqi: 45
  };
  
  // Build response payload
  var payload = {
    timestamp: today.toISOString(),
    date: Utilities.formatDate(today, Session.getScriptTimeZone(), "EEEE, MMM d"),
    time: Utilities.formatDate(today, Session.getScriptTimeZone(), "h:mm a"),
    
    next_event: nextEvent,
    
    todos: todos.length > 0 ? todos : ["No tasks pending"],
    
    isaac_aligners: {
      day_current: diffDays,
      day_total: totalDays,
      percent_complete: percentComplete,
      next_change: "Tuesday (" + daysUntilTuesday + " days)",
      message: diffDays % 7 < 2 ? "⚠ CHANGE ALIGNERS" : "On track"
    },
    
    weather: weather,
    
    update_interval_seconds: 1800, // 30 minutes
    
    motivational_quote: getMotivationalQuote()
  };
  
  return ContentService.createTextOutput(JSON.stringify(payload, null, 2))
    .setMimeType(ContentService.MimeType.JSON);
}

function getMotivationalQuote() {
  var quotes = [
    "Calm Mind, Driven Performance",
    "Steady Heart, No Drop",
    "SaaS is Dead, Loyalty is King",
    "Build with Purpose"
  ];
  
  var index = new Date().getDate() % quotes.length;
  return quotes[index];
}

/**
 * Test function - run this to verify your setup
 */
function testAPI() {
  var response = doGet();
  Logger.log(response.getContent());
}
