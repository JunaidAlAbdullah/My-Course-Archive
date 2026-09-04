@echo off
echo Compiling Online Ticket Booking System...
javac mainx.java
if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! You can now run: java mainx
) else (
    echo Compilation failed!
)
pause
