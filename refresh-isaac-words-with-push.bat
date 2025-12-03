@echo off
REM =============================================================================
REM Quote/Word Auto-Update with GitHub Push
REM Updates isaac word templates every 5 minutes and pushes to GitHub
REM =============================================================================

setlocal enabledelayedexpansion

:loop
    cls
    echo ============================================================================
    echo  ISAAC'S WORDS AUTO-UPDATER (with GitHub Push)
    echo  Time: %date% %time%
    echo ============================================================================
    echo.
    
    REM Run the Python word generator
    echo [%time%] Generating new Isaac word templates...
    python isaac_word_generator.py
    
    REM Check if generation was successful
    if %ERRORLEVEL% EQU 0 (
        echo.
        echo [%time%] ✓ Templates generated successfully
        echo [%time%] Pushing to GitHub...
        
        REM Stage all generated templates
        git add isaac-words\templates\*.json
        
        REM Check if there are changes to commit
        git diff --cached --quiet
        if %ERRORLEVEL% NEQ 0 (
            REM Commit with timestamp
            for /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set mydate=%%c-%%a-%%b)
            for /f "tokens=1-2 delims=/:" %%a in ('time /t') do (set mytime=%%a%%b)
            
            git commit -m "Auto-update Isaac words templates - !mydate! !mytime!"
            git push origin main
            
            echo [%time%] ✓ Pushed to GitHub
        ) else (
            echo [%time%] No changes to push
        )
    ) else (
        echo [%time%] ✗ Template generation failed
    )
    
    echo.
    echo [%time%] Next update in 5 minutes...
    echo ============================================================================
    echo.
    
    REM Wait 5 minutes (300 seconds)
    timeout /t 300 /nobreak
    
    goto loop

:end
pause
