# Online Ticket Booking System

A complete Java OOP project built with Java Swing for the user interface and text files for storing data.

## Features

✅ **User Registration and Login**
- Create new accounts
- Secure password hashing (SHA-256)
- Role-based access (Admin/User)

✅ **Event Catalog and Search**
- Browse available events in tables
- Search by type, location, and date
- Event details (title, location, date, price, seats)

✅ **Ticket Booking and Live Availability**
- Book tickets with seat selection
- Live seat count updates
- Unique booking IDs
- Booking confirmations

✅ **User Dashboard**
- View upcoming and past bookings
- Cancel bookings (increases seat availability)
- Personal booking history

✅ **Admin Panel**
- Add, update, and remove events
- Update ticket prices and availability
- Generate sales reports
- View all bookings

✅ **Extra Features**
- Light/Dark theme switching
- Modern UI with styled buttons
- Responsive design
- Error handling and validation

## How to Run

### Prerequisites
- Java 8 or higher (JDK)
- Windows Command Prompt or Git Bash

### Method 1: One Command (Recommended)
```cmd
java mainx
```

### Method 2: Compile then Run
```cmd
javac mainx.java
java mainx
```

### Method 3: Double-click Batch File
```cmd
run.bat
```

## Login Credentials

### Default Admin Account
- **Username:** `admin`
- **Password:** `admin123`
- **Role:** Administrator

### Default User Account
- **Username:** `user`
- **Password:** `user123`
- **Role:** Regular User

### Register New Users
- Click "Register" button
- Fill in username, password, full name, and email
- New users can immediately login

## Project Structure

```
Project/final/
├── mainx.java          ← Single file containing everything!
├── mainx.class         ← Compiled version
├── run.bat            ← Windows batch file
└── README.md          ← This file
```

## Technical Details

- **Architecture:** Single-file Java application
- **UI Framework:** Java Swing
- **Data Storage:** In-memory (can be extended to files)
- **Password Security:** SHA-256 hashing
- **Design Pattern:** MVC-like structure
- **OOP Principles:** Encapsulation, Inheritance, Polymorphism

## Sample Data

The system comes pre-loaded with 5 sample events:
1. Rock Concert 2024
2. Shakespeare Festival
3. Tech Conference 2024
4. Basketball Championship
5. Cooking Workshop

## Usage Instructions

1. **Login** with admin or user credentials
2. **Admin Panel:**
   - Add new events
   - View all events and bookings
   - Generate sales reports
3. **User Panel:**
   - Browse available events
   - Book tickets
   - View and cancel bookings
4. **Theme:** Toggle between light and dark modes

## Perfect for Learning

- **Simple Structure:** Everything in one file
- **Easy to Modify:** Change colors, add features
- **No Dependencies:** Pure Java, no external libraries
- **Beginner Friendly:** Clear code organization
- **Professional Features:** Real-world functionality

Just run `java mainx` and you're ready to go! 🚀
