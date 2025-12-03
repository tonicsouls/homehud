@echo off
REM Auto-refresh RSS feeds every 30 minutes
REM Run in background to keep news feeds updated

setlocal enabledelayedexpansion

set SCRIPT_DIR=C:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD
set PYTHON_EXE=python
set INTERVAL=1800

echo.
echo =====================================
echo RSS Feed Auto-Refresh Service
echo =====================================
echo.
echo Script Dir: %SCRIPT_DIR%
echo Refresh Interval: %INTERVAL% seconds (30 minutes)
echo.
echo Starting RSS auto-refresh loop...
echo Press Ctrl+C to stop
echo.

cd /d "%SCRIPT_DIR%"

:loop
echo.
echo [%date% %time%] Refreshing RSS feeds...
%PYTHON_EXE% rss_feed_updater.py

echo Waiting %INTERVAL% seconds until next refresh...
timeout /t %INTERVAL% /nobreak

goto loop
