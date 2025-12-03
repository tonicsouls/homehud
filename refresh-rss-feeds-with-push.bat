@echo off
REM =============================================================================
REM RSS Feed Auto-Update with GitHub Push
REM Updates pokemon news template every 30 minutes and pushes to GitHub
REM =============================================================================

setlocal enabledelayedexpansion

:loop
    cls
    echo ============================================================================
    echo  RSS FEED AUTO-UPDATER (with GitHub Push)
    echo  Time: %date% %time%
    echo ============================================================================
    echo.
    
    REM Run the Python RSS updater
    echo [%time%] Running RSS feed updater...
    python rss_feed_updater.py
    
    REM Check if update was successful
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo [%time%] ✓ RSS feed updated successfully
        echo [%time%] Pushing to GitHub...
        
        REM Stage changes
        git add templates\pokemon-beach-news-updated.json pokemon-news\templates\pokemon-beach-news-updated.json
        
        REM Check if there are changes to commit
        git diff --cached --quiet
        if %ERRORLEVEL% NEQ 0 (
            REM Commit with timestamp
            for /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set mydate=%%c-%%a-%%b)
            for /f "tokens=1-2 delims=/:" %%a in ('time /t') do (set mytime=%%a%%b)
            
            git commit -m "Auto-update RSS feed - !mydate! !mytime!"
            git push origin main
            
            echo [%time%] ✓ Pushed to GitHub
        ) else (
            echo [%time%] No changes to push
        )
    ) else (
        echo [%time%] ✗ RSS feed update failed
    )
    
    echo.
    echo [%time%] Next update in 30 minutes...
    echo ============================================================================
    echo.
    
    REM Wait 30 minutes (1800 seconds)
    timeout /t 1800 /nobreak
    
    goto loop

:end
pause
