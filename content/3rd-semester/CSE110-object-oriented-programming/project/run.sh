#!/bin/bash
echo "Compiling Online Ticket Booking System..."
javac mainx.java
if [ $? -eq 0 ]; then
    echo "Compilation successful!"
    echo "Starting application..."
    java mainx
else
    echo "Compilation failed!"
    read -p "Press Enter to continue..."
fi
