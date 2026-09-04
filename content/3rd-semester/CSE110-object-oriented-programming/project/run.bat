@echo off
echo Compiling Online Ticket Booking System...
javac mainx.java
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful!
    echo Starting application...
    java mainx
) else (
    echo Compilation failed!
    pause
)
