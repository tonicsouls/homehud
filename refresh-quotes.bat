@echo off
REM Auto-refresh quote templates every 5 minutes
REM Run this script in background for continuous updates

setlocal enabledelayedexpansion

REM Set your paths here
set SCRIPT_DIR=C:\Users\Darry\OneDrive\Brain Candy portal OMBU\ROOT_BODY_X\Spine_plans\HOMEHUD
set PYTHON_EXE=python
set INTERVAL=300

echo.
echo =====================================
echo Quote Auto-Refresh Service
echo =====================================
echo.
echo Script Dir: %SCRIPT_DIR%
echo Refresh Interval: %INTERVAL% seconds (5 minutes)
echo.
echo Starting auto-refresh loop...
echo Press Ctrl+C to stop
echo.

cd /d "%SCRIPT_DIR%"

:loop
echo.
echo [%date% %time%] Refreshing quotes...
%PYTHON_EXE% dashboard_updater.py
if errorlevel 1 (
    echo ERROR: Quote refresh failed!
) else (
    echo SUCCESS: Quotes updated
)

echo Waiting %INTERVAL% seconds until next refresh...
timeout /t %INTERVAL% /nobreak

goto loop
