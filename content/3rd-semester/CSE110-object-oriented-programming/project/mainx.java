import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.*;
import javax.swing.*;

public class mainx 
{
    private static ArrayList<User> users = new ArrayList<>();
    private static ArrayList<User> admins = new ArrayList<>();
    private static ArrayList<Event> events = new ArrayList<>();
    private static ArrayList<Booking> bookings = new ArrayList<>();
    private static String currentUser = "";
    private static boolean isAdmin = false;
    private static boolean isDarkMode = false;

    private static final String USERS_FILE = "users.txt";
    private static final String ADMINS_FILE = "admins.txt";
    private static final String EVENTS_FILE = "events.txt";
    private static final String BOOKINGS_FILE = "bookings.txt";

    public static void main(String[] args) 
    {
        loadData();
        showLoginFrame();
    }

    private static void showLoginFrame() 
    {
        JFrame frame = new JFrame("Online Ticket Booking System");
        frame.setSize(900, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        // Set the background image
        JLabel background = new JLabel(new ImageIcon("login page.png"));
        background.setLayout(null); // Allow absolute positioning of components

        // Username label
        JLabel userLabel = new JLabel("Username:");
        userLabel.setFont(new Font("Arial", Font.BOLD, 14));
        userLabel.setForeground(Color.BLACK);
        userLabel.setBounds(250, 210, 100, 35); // Position on the ticket body
        background.add(userLabel);

        // Username field
        JTextField userField = new JTextField();
        userField.setBounds(350, 210, 250, 35); // Position on the ticket body
        userField.setFont(new Font("Arial", Font.PLAIN, 14));
        userField.setBorder(BorderFactory.createLineBorder(Color.GRAY));
        background.add(userField);

        // Password label
        JLabel passLabel = new JLabel("Password:");
        passLabel.setFont(new Font("Arial", Font.BOLD, 14));
        passLabel.setForeground(Color.BLACK);
        passLabel.setBounds(250, 260, 100, 35); // Position on the ticket body
        background.add(passLabel);

        // Password field
        JPasswordField passField = new JPasswordField();
        passField.setBounds(350, 260, 250, 35); // Position on the ticket body
        passField.setFont(new Font("Arial", Font.PLAIN, 14));
        passField.setBorder(BorderFactory.createLineBorder(Color.GRAY));
        background.add(passField);

        // Login button
        JButton loginBtn = new JButton("Login");
        loginBtn.setBounds(350, 310, 120, 40); // Position on the ticket body
        loginBtn.setBackground(new Color(58, 110, 165));
        loginBtn.setForeground(Color.WHITE);
        loginBtn.setFont(new Font("Arial", Font.BOLD, 14));
        loginBtn.addActionListener(e -> {
            String user = userField.getText().trim();
            String pass = new String(passField.getPassword());

            if (user.isEmpty() || pass.isEmpty()) 
            {
                JOptionPane.showMessageDialog(frame, "Please enter both username and password!", "Error",
                        JOptionPane.ERROR_MESSAGE);
                return;
            }

            if (loginUser(user, pass)) 
            {
                frame.dispose();
                if (isAdmin) 
                {
                    showAdminPanel();
                } 
                else 
                {
                    showUserPanel();
                }
            } 
            else 
            {
                JOptionPane.showMessageDialog(frame, "Invalid username or password!", "Login Failed",
                        JOptionPane.ERROR_MESSAGE);
                passField.setText("");
            }
        });
        background.add(loginBtn);

        // Register button
        JButton regBtn = new JButton("Register");
        regBtn.setBounds(480, 310, 120, 40); // Position on the ticket body
        regBtn.setBackground(new Color(52, 168, 83));
        regBtn.setForeground(Color.WHITE);
        regBtn.setFont(new Font("Arial", Font.BOLD, 14));
        regBtn.addActionListener(e -> showRegisterFrame());
        background.add(regBtn);

        // Add the background to the frame
        frame.add(background);
        frame.setVisible(true);
    }

    private static void showRegisterFrame() 
    {
        JFrame frame = new JFrame("User Registration");
        frame.setSize(400, 300);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);

        JLabel usernameLabel = new JLabel("Username:");
        usernameLabel.setBounds(50, 50, 100, 30);
        frame.add(usernameLabel);

        JTextField usernameField = new JTextField();
        usernameField.setBounds(150, 50, 200, 30);
        frame.add(usernameField);

        JLabel passwordLabel = new JLabel("Password:");
        passwordLabel.setBounds(50, 100, 100, 30);
        frame.add(passwordLabel);

        JPasswordField passwordField = new JPasswordField();
        passwordField.setBounds(150, 100, 200, 30);
        frame.add(passwordField);

        JButton registerButton = new JButton("Register");
        registerButton.setBounds(150, 150, 100, 30);
        frame.add(registerButton);

        registerButton.addActionListener(e -> {
            String username = usernameField.getText().trim();
            String password = new String(passwordField.getPassword()).trim();

            if (username.isEmpty() || password.isEmpty()) 
            {
                JOptionPane.showMessageDialog(frame, "Username and password cannot be empty!");
                return;
            }

            // Check if the username already exists in users or admins
            for (User user : users) 
            {
                if (user.username.equals(username)) 
                {
                    JOptionPane.showMessageDialog(frame, "Username already exists!");
                    return;
                }
            }
            for (User admin : admins) 
            {
                if (admin.username.equals(username)) 
                {
                    JOptionPane.showMessageDialog(frame, "Username already exists!");
                    return;
                }
            }

            // Add the new user to the list
            users.add(new User(username, password, "Default Full Name", "default@example.com", false));
            saveData();
            JOptionPane.showMessageDialog(frame, "User registered successfully!");

            frame.dispose(); // Close the registration frame
            showLoginFrame(); // Return to the login interface
        });

        frame.setVisible(true);
    }

    private static void showAdminPanel() 
    {
        JFrame frame = new JFrame("Admin Panel - " + currentUser);
        frame.setSize(1200, 800);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        // Set the background image
        JLabel background = new JLabel(new ImageIcon("admin interface.png"));
        background.setLayout(null); // Allow absolute positioning of components
        background.setBounds(0, 0, 1200, 800); // Match the frame size

        // Create a panel for buttons
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        buttonPanel.setOpaque(false); // Make the panel transparent
        buttonPanel.setBounds(50, 50, 1100, 100); // Position the panel on the background

        JButton addEventBtn = createStyledButton("Add Event", new Color(40, 167, 69));
        JButton viewEventsBtn = createStyledButton("View Events", new Color(58, 110, 165));
        JButton viewBookingsBtn = createStyledButton("View Bookings", new Color(255, 193, 7));
        JButton reportsBtn = createStyledButton("Reports", new Color(220, 53, 69));
        JButton logoutBtn = createStyledButton("Logout", new Color(108, 117, 125));

        addEventBtn.addActionListener(e -> addEvent());
        viewEventsBtn.addActionListener(e -> viewEvents());
        viewBookingsBtn.addActionListener(e -> viewBookings());
        reportsBtn.addActionListener(e -> showReports());
        logoutBtn.addActionListener(e -> {
            frame.dispose();
            currentUser = "";
            isAdmin = false;
            showLoginFrame();
        });

        buttonPanel.add(addEventBtn);
        buttonPanel.add(viewEventsBtn);
        buttonPanel.add(viewBookingsBtn);
        buttonPanel.add(reportsBtn);
        buttonPanel.add(logoutBtn);

        background.add(buttonPanel); // Add the button panel to the background
        frame.add(background); // Add the background to the frame
        frame.setVisible(true);
    }

    private static void showUserPanel() 
    {
        JFrame frame = new JFrame("User Panel - " + currentUser);
        frame.setSize(1200, 800);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        // Set the background image
        JLabel background = new JLabel(new ImageIcon("welcome to.png"));
        background.setLayout(null); // Allow absolute positioning of components
        background.setBounds(0, 0, 1200, 800); // Match the frame size

        // Create a panel for buttons
        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        buttonPanel.setOpaque(false); // Make the panel transparent
        buttonPanel.setBounds(50, 50, 1100, 100); // Position the panel on the background

        JButton viewEventsBtn = createStyledButton("Browse Events", new Color(58, 110, 165));
        JButton bookEventBtn = createStyledButton("Book Event", new Color(40, 167, 69));
        JButton myBookingsBtn = createStyledButton("My Bookings", new Color(255, 193, 7));
        JButton logoutBtn = createStyledButton("Logout", new Color(108, 117, 125));

        viewEventsBtn.addActionListener(e -> viewEvents());
        bookEventBtn.addActionListener(e -> bookEvent());
        myBookingsBtn.addActionListener(e -> viewMyBookings());
        logoutBtn.addActionListener(e -> {
            frame.dispose();
            currentUser = "";
            isAdmin = false;
            showLoginFrame();
        });

        buttonPanel.add(viewEventsBtn);
        buttonPanel.add(bookEventBtn);
        buttonPanel.add(myBookingsBtn);
        buttonPanel.add(logoutBtn);

        background.add(buttonPanel); // Add the button panel to the background
        frame.add(background); // Add the background to the frame
        frame.setVisible(true);
    }

    private static JButton createStyledButton(String text, Color bgColor) 
    {
        JButton button = new JButton(text);
        button.setBackground(bgColor);
        button.setForeground(Color.WHITE);
        button.setFont(new Font("Arial", Font.BOLD, 12));
        button.setPreferredSize(new Dimension(120, 35));
        button.setFocusPainted(false);
        return button;
    }

    private static void addEvent() 
    {
        JFrame frame = new JFrame("Add New Event");
        frame.setSize(500, 600);
        frame.setLocationRelativeTo(null);

        JLabel titleLabel = new JLabel("Add New Event", SwingConstants.CENTER);
        titleLabel.setFont(new Font("Arial", Font.BOLD, 20));
        titleLabel.setBounds(150, 20, 200, 30);
        frame.add(titleLabel);

        // Form fields
        String[] labels = { "Title:", "Type:", "Location:", "Date (YYYY-MM-DD):", "Time (HH:MM):", "Price ($):",
                "Total Seats:", "Description:" };
        JTextField[] fields = new JTextField[8];

        for (int i = 0; i < labels.length; i++) 
        {
            JLabel label = new JLabel(labels[i]);
            label.setBounds(50, 70 + i * 50, 150, 25);
            frame.add(label);

            fields[i] = new JTextField();
            fields[i].setBounds(200, 70 + i * 50, 200, 25);
            frame.add(fields[i]);
        }

        // Save button
        JButton saveBtn = new JButton("Save Event");
        saveBtn.setBounds(150, 450, 100, 35);
        saveBtn.setBackground(new Color(40, 167, 69));
        saveBtn.setForeground(Color.WHITE);
        saveBtn.addActionListener(e -> {
            try 
            {
                String title = fields[0].getText().trim();
                String type = fields[1].getText().trim();
                String location = fields[2].getText().trim();
                String date = fields[3].getText().trim();
                String time = fields[4].getText().trim();
                double price = Double.parseDouble(fields[5].getText().trim());
                int seats = Integer.parseInt(fields[6].getText().trim());
                String description = fields[7].getText().trim();

                if (title.isEmpty() || type.isEmpty() || location.isEmpty() || date.isEmpty() || time.isEmpty()) 
                {
                    JOptionPane.showMessageDialog(frame, "All fields are required!", "Error",
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }

                Event event = new Event(
                        "evt-" + System.currentTimeMillis(),
                        title, type, location, date + " " + time,
                        price, seats, description);
                events.add(event);
                saveData();
                JOptionPane.showMessageDialog(frame, "Event added successfully!", "Success",
                        JOptionPane.INFORMATION_MESSAGE);
                frame.dispose();
            } 
            catch (NumberFormatException ex) 
            {
                JOptionPane.showMessageDialog(frame, "Please enter valid numbers for price and seats!", "Error",
                        JOptionPane.ERROR_MESSAGE);
            } 
            catch (Exception ex) 
            {
                JOptionPane.showMessageDialog(frame, "Error: " + ex.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
            }
        });
        frame.add(saveBtn);

        frame.setLayout(null);
        frame.setVisible(true);
    }

    private static void viewEvents() 
    {
        JFrame frame = new JFrame("All Events");
        frame.setSize(1000, 700);
        frame.setLocationRelativeTo(null);

        String[] columns = { "ID", "Title", "Type", "Location", "Date & Time", "Price", "Available Seats",
                "Description" };
        Object[][] data = new Object[events.size()][8];

        for (int i = 0; i < events.size(); i++)
        {
            Event event = events.get(i);
            data[i][0] = event.id;
            data[i][1] = event.title;
            data[i][2] = event.type;
            data[i][3] = event.location;
            data[i][4] = event.dateTime;
            data[i][5] = "$" + String.format("%.2f", event.price);
            data[i][6] = event.availableSeats;
            data[i][7] = event.description;
        }

        JTable table = new JTable(data, columns);
        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setBounds(20, 20, 950, 600);
        frame.add(scrollPane);

        frame.setLayout(null);
        frame.setVisible(true);
    }

    private static void bookEvent()
    {
        if (events.isEmpty()) 
        {
            JOptionPane.showMessageDialog(null, "No events available!", "Info", JOptionPane.INFORMATION_MESSAGE);
            return;
        }

        String[] eventNames = new String[events.size()];
        for (int i = 0; i < events.size(); i++) 
        {
            Event event = events.get(i);
            eventNames[i] = event.title + " - " + event.location + " ($" + String.format("%.2f", event.price) + ")";
        }

        String selectedEvent = (String) JOptionPane.showInputDialog(null,
                "Select an event to book:", "Book Event", JOptionPane.QUESTION_MESSAGE, null, eventNames,
                eventNames[0]);

        if (selectedEvent != null) 
        {
            String eventTitle = selectedEvent.split(" - ")[0];
            Event event = null;
            for (Event e : events) 
            {
                if (e.title.equals(eventTitle)) 
                {
                    event = e;
                    break;
                }
            }

            if (event != null && event.availableSeats > 0) 
            {
                String seatsStr = JOptionPane
                        .showInputDialog("How many seats? (Available: " + event.availableSeats + ")");
                try 
                {
                    int seats = Integer.parseInt(seatsStr);
                    if (seats > 0 && seats <= event.availableSeats) 
                    {
                        Booking booking = new Booking(
                                "bkg-" + System.currentTimeMillis(),
                                currentUser,
                                event.id,
                                seats,
                                seats * event.price);
                        bookings.add(booking);
                        event.availableSeats -= seats;
                        saveData();

                        JOptionPane.showMessageDialog(null,
                                "Booking successful! Total: $" + String.format("%.2f", seats * event.price),
                                "Success", JOptionPane.INFORMATION_MESSAGE);
                    } 
                    else 
                    {
                        JOptionPane.showMessageDialog(null, "Invalid number of seats!", "Error",
                                JOptionPane.ERROR_MESSAGE);
                    }
                } 
                
                catch (NumberFormatException ex) 
                {
                    JOptionPane.showMessageDialog(null, "Please enter a valid number!", "Error",
                            JOptionPane.ERROR_MESSAGE);
                }
            } 
            else 
            {
                JOptionPane.showMessageDialog(null, "No seats available for this event!", "Error",
                        JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private static void viewBookings() 
    {
        JFrame frame = new JFrame("All Bookings");
        frame.setSize(1000, 700);
        frame.setLocationRelativeTo(null);

        String[] columns = { "ID", "User", "Event", "Seats", "Total Price", "Date" };
        Object[][] data = new Object[bookings.size()][6];

        for (int i = 0; i < bookings.size(); i++) 
        {
            Booking booking = bookings.get(i);
            data[i][0] = booking.id;
            data[i][1] = getUserFullName(booking.userId);
            data[i][2] = getEventTitle(booking.eventId);
            data[i][3] = booking.seats;
            data[i][4] = "$" + String.format("%.2f", booking.totalPrice);
            data[i][5] = booking.date;
        }

        JTable table = new JTable(data, columns);
        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setBounds(20, 20, 950, 600);
        frame.add(scrollPane);

        frame.setLayout(null);
        frame.setVisible(true);
    }

    private static void viewMyBookings() 
    {
        JFrame frame = new JFrame("My Bookings - " + currentUser);
        frame.setSize(1000, 700);
        frame.setLocationRelativeTo(null);

        ArrayList<Booking> myBookings = new ArrayList<>();
        for (Booking b : bookings) {
            if (b.userId.equals(currentUser)) 
            {
                myBookings.add(b);
            }
        }

        if (myBookings.isEmpty()) 
        {
            JOptionPane.showMessageDialog(frame, "You have no bookings yet!", "Info", JOptionPane.INFORMATION_MESSAGE);
            return;
        }

        String[] columns = { "ID", "Event", "Seats", "Total Price", "Date", "Action" };
        Object[][] data = new Object[myBookings.size()][6];

        for (int i = 0; i < myBookings.size(); i++) 
        {
            Booking booking = myBookings.get(i);
            data[i][0] = booking.id;
            data[i][1] = getEventTitle(booking.eventId);
            data[i][2] = booking.seats;
            data[i][3] = "$" + String.format("%.2f", booking.totalPrice);
            data[i][4] = booking.date;
            data[i][5] = "Cancel";
        }

        JTable table = new JTable(data, columns);
        table.addMouseListener(new MouseAdapter() 
        {
            @Override
            public void mouseClicked(MouseEvent e) 
            {
                int row = table.getSelectedRow();
                int col = table.getSelectedColumn();

                if (col == 5 && row >= 0) 
                { // Cancel button clicked
                    String bookingId = (String) table.getValueAt(row, 0);
                    String eventTitle = (String) table.getValueAt(row, 1);

                    int choice = JOptionPane.showConfirmDialog(frame,
                            "Are you sure you want to cancel your booking for '" + eventTitle + "'?",
                            "Confirm Cancellation", JOptionPane.YES_NO_OPTION);

                    if (choice == JOptionPane.YES_OPTION) 
                    {
                        cancelBooking(bookingId);
                        frame.dispose();
                        viewMyBookings();
                    }
                }
            }
        });

        JScrollPane scrollPane = new JScrollPane(table);
        scrollPane.setBounds(20, 20, 950, 600);
        frame.add(scrollPane);

        frame.setLayout(null);
        frame.setVisible(true);
    }

    private static void showReports() 
    {
        JFrame frame = new JFrame("Sales Reports");
        frame.setSize(600, 500);
        frame.setLocationRelativeTo(null);

        JTextArea reportArea = new JTextArea();
        reportArea.setEditable(false);
        reportArea.setFont(new Font("Monospaced", Font.PLAIN, 12));

        // Calculate reports
        double totalRevenue = 0;
        Map<String, Integer> eventBookings = new HashMap<>();

        for (Booking b : bookings) 
        {
            totalRevenue += b.totalPrice;
            String eventTitle = getEventTitle(b.eventId);
            eventBookings.put(eventTitle, eventBookings.getOrDefault(eventTitle, 0) + 1);
        }

        StringBuilder report = new StringBuilder();
        report.append("=== SALES REPORT ===\n\n");
        report.append("Total Revenue: $").append(String.format("%.2f", totalRevenue)).append("\n");
        report.append("Total Bookings: ").append(bookings.size()).append("\n\n");
        report.append("Bookings per Event:\n");
        report.append("==================\n");

        eventBookings.entrySet().stream()
                .sorted(Map.Entry.<String, Integer>comparingByValue().reversed())
                .forEach(entry -> {
                    report.append(entry.getKey()).append(": ").append(entry.getValue()).append(" bookings\n");
                });

        reportArea.setText(report.toString());

        JScrollPane scrollPane = new JScrollPane(reportArea);
        scrollPane.setBounds(20, 20, 550, 400);
        frame.add(scrollPane);

        frame.setLayout(null);
        frame.setVisible(true);
    }

    private static void cancelBooking(String bookingId) 
    {
        for (int i = 0; i < bookings.size(); i++) 
        {
            if (bookings.get(i).id.equals(bookingId))
            {
                Booking booking = bookings.get(i);

                // Increase available seats
                for (Event event : events) 
                {
                    if (event.id.equals(booking.eventId)) 
                    {
                        event.availableSeats += booking.seats;
                        break;
                    }
                }

                // Remove booking
                bookings.remove(i);
                saveData();

                JOptionPane.showMessageDialog(null, "Booking cancelled successfully!", "Success",
                        JOptionPane.INFORMATION_MESSAGE);
                return;
            }
        }
    }

    private static boolean loginUser(String username, String password) 
    {
        for (User admin : admins) 
        {
            if (admin.username.equals(username) && admin.passwordHash.equals(password))
            {
                currentUser = username;
                isAdmin = true;
                return true;
            }
        }

        for (User user : users) 
        {
            if (user.username.equals(username) && user.passwordHash.equals(password)) 
            {
                currentUser = username;
                isAdmin = false;
                return true;
            }
        }
        return false;
    }

    private static boolean registerUser(String username, String password, String fullName, String email) 
    {
        // Check if username already exists
        for (User user : users) 
        {
            if (user.username.equals(username)) 
            {
                return false;
            }
        }

        // Create new user
        String hashedPassword = hashPassword(password);
        User newUser = new User(username, hashedPassword, fullName, email, false);
        users.add(newUser);
        saveData();
        return true;
    }

    private static String hashPassword(String password) 
    {
        try 
        {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(password.getBytes(StandardCharsets.UTF_8));
            StringBuilder hexString = new StringBuilder();
            for (byte b : hash) 
            {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1)
                    hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } 
        catch (Exception e) 
        {
            return password; // Fallback to plain text if hashing fails
        }
    }

    private static boolean verifyPassword(String password, String hash) 
    {
        return hashPassword(password).equals(hash);
    }

    private static String getEventTitle(String eventId) 
    {
        for (Event e : events) 
        {
            if (e.id.equals(eventId)) 
            {
                return e.title;
            }
        }
        return "Unknown Event";
    }

    private static String getUserFullName(String username) {
        for (User u : users) 
        {
            if (u.username.equals(username)) 
            {
                return u.fullName;
            }
        }
        for (User a : admins) 
        {
            if (a.username.equals(username)) 
            {
                return a.fullName;
            }
        }
        return username;
    }

    private static void loadData() 
    {
        users.clear();
        admins.clear();
        events.clear();
        bookings.clear();

        // Load admins
        try (BufferedReader br = new BufferedReader(new FileReader(ADMINS_FILE))) 
        {
            String line;
            while ((line = br.readLine()) != null) 
            {
                String[] parts = line.split(",");
                if (parts.length >= 4) 
                {
                    admins.add(new User(parts[0], parts[1], parts[2], parts[3], true));
                }
            }
        } 
        catch (IOException e) 
        {
            // If file doesn't exist, add default admin
            admins.add(new User("admin", "admin123", "System Administrator", "admin@tbs.com", true));
            saveData();
        }

        // Load users
        try (BufferedReader br = new BufferedReader(new FileReader(USERS_FILE))) 
        {
            String line;
            while ((line = br.readLine()) != null) 
            {
                String[] parts = line.split(",");
                if (parts.length >= 4) 
                {
                    users.add(new User(parts[0], parts[1], parts[2], parts[3], false));
                }
            }
        } 
        catch (IOException e) 
        {
            // If file doesn't exist, add default user
            users.add(new User("user", "user123", "Regular User", "user@tbs.com", false));
            saveData();
        }

        // Load events
        try (BufferedReader br = new BufferedReader(new FileReader(EVENTS_FILE))) 
        {
            String line;
            while ((line = br.readLine()) != null) 
            {
                String[] parts = line.split(",");
                if (parts.length >= 8) 
                {
                    events.add(new Event(parts[0], parts[1], parts[2], parts[3], parts[4],
                            Double.parseDouble(parts[5]), Integer.parseInt(parts[6]), parts[7]));
                }
            }
        } 
        catch (IOException e) 
        {
            // Add sample events if file doesn't exist
            events.add(new Event("evt-1", "Rock Concert 2024", "Concert", "Madison Square Garden", "2024-12-25 20:00",
                    75.0, 100, "Amazing rock concert featuring top artists"));
            events.add(new Event("evt-2", "Shakespeare Festival", "Theater", "Central Park", "2024-12-20 19:30", 45.0,
                    50, "Classic Shakespeare plays under the stars"));
            events.add(new Event("evt-3", "Tech Conference 2024", "Conference", "Convention Center", "2024-12-30 09:00",
                    150.0, 30, "Annual technology conference with industry leaders"));
            events.add(new Event("evt-4", "Basketball Championship", "Sports", "Sports Arena", "2024-12-28 18:00", 60.0,
                    80, "Championship basketball game"));
            events.add(new Event("evt-5", "Cooking Workshop", "Workshop", "Culinary Institute", "2024-12-22 14:00",
                    25.0, 50, "Learn to cook delicious Italian cuisine"));
            saveData();
        }

        // Load bookings
        try (BufferedReader br = new BufferedReader(new FileReader(BOOKINGS_FILE))) 
        {
            String line;
            while ((line = br.readLine()) != null) 
            {
                String[] parts = line.split(",");
                if (parts.length >= 6) 
                {
                    Booking b = new Booking(parts[0], parts[1], parts[2], Integer.parseInt(parts[3]),
                            Double.parseDouble(parts[4]));
                    b.date = parts[5];
                    bookings.add(b);
                }
            }
        } 
        catch (IOException e) 
        {
            // No bookings yet
        }
    }

    private static void saveData() 
    {
        // Save admins
        try (PrintWriter pw = new PrintWriter(new FileWriter(ADMINS_FILE))) 
        {
            for (User u : admins) 
            {
                pw.println(u.username + "," + u.passwordHash + "," + u.fullName + "," + u.email);
            }
        } 
        catch (IOException e) 
        {
            e.printStackTrace();
        }

        // Save users
        try (PrintWriter pw = new PrintWriter(new FileWriter(USERS_FILE))) 
        {
            for (User u : users)
            {
                pw.println(u.username + "," + u.passwordHash + "," + u.fullName + "," + u.email);
            }
        } 
        catch (IOException e) 
        {
            e.printStackTrace();
        }

        // Save events
        try (PrintWriter pw = new PrintWriter(new FileWriter(EVENTS_FILE))) 
        {
            for (Event ev : events) 
            {
                pw.println(ev.id + "," + ev.title + "," + ev.type + "," + ev.location + "," + ev.dateTime + "," +
                        ev.price + "," + ev.availableSeats + "," + ev.description);
            }
        } 
        catch (IOException e) 
        {
            e.printStackTrace();
        }

        // Save bookings
        try (PrintWriter pw = new PrintWriter(new FileWriter(BOOKINGS_FILE))) 
        {
            for (Booking b : bookings) 
            {
                pw.println(b.id + "," + b.userId + "," + b.eventId + "," + b.seats + "," + b.totalPrice + "," + b.date);
            }
        } 
        
        catch (IOException e) 
        {
            e.printStackTrace();
        }
    }

    // Data classes
    static class User 
    {
        String username, passwordHash, fullName, email;
        boolean isAdmin;

        User(String username, String passwordHash, String fullName, String email, boolean isAdmin) 
        {
            this.username = username;
            this.passwordHash = passwordHash;
            this.fullName = fullName;
            this.email = email;
            this.isAdmin = isAdmin;
        }
    }

    static class Event 
    {
        String id, title, type, location, dateTime, description;
        double price;
        int totalSeats, availableSeats;

        Event(String id, String title, String type, String location, String dateTime, double price, int seats, String description) 
        {
            this.id = id;
            this.title = title;
            this.type = type;
            this.location = location;
            this.dateTime = dateTime;
            this.price = price;
            this.totalSeats = seats;
            this.availableSeats = seats;
            this.description = description;
        }
    }

    static class Booking 
    {
        String id, userId, eventId, date;
        int seats;
        double totalPrice;

        Booking(String id, String userId, String eventId, int seats, double totalPrice) 
        {
            this.id = id;
            this.userId = userId;
            this.eventId = eventId;
            this.seats = seats;
            this.totalPrice = totalPrice;
            this.date = new Date().toString();
        }
    }
}