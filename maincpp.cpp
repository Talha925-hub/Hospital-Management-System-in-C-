#include <windows.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cctype>
#include "Person.h"
#include "Patient.h"
#include "Doctor.h"
#include "SpecialistDoctor.h"
#include "Nurse.h"
#include "CateringStaff.h"
#include "Receptionist.h"
#include "SecurityGuard.h"
#include "Driver.h"
#include "Cleaner.h"
#include "Ambulance.h"

using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

// Custom pause function
void pause() {
    SetConsoleTextAttribute(h, 3);
    cout << "\nPress Enter to continue...";
    cin.get();
}

// Login function with properly aligned and attractive UI
bool login() {
    const int MAX_ATTEMPTS = 3;
    int attempts = 0;
    string username, password;
    bool usernameActive = true;
    bool passwordActive = false;

    // Create full-screen SFML window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Hospital Management System - Login", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("times new roman.ttf")) {
        if (!font.loadFromFile("C:\\Windows\\Fonts\\times.ttf")) {
            cout << "Error: Could not load font file. Using Arial instead.\n";
            font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");
        }
    }

    // Calculate scaling factors
    float scale = min(desktop.width / 1920.0f, desktop.height / 1080.0f);

    // Create gradient background
    sf::VertexArray background(sf::Quads, 4);
    background[0].position = sf::Vector2f(0, 0);
    background[1].position = sf::Vector2f(desktop.width, 0);
    background[2].position = sf::Vector2f(desktop.width, desktop.height);
    background[3].position = sf::Vector2f(0, desktop.height);
    background[0].color = sf::Color(30, 144, 255);  // Dodger Blue
    background[1].color = sf::Color(65, 105, 225);  // Royal Blue
    background[2].color = sf::Color(0, 0, 139);     // Dark Blue
    background[3].color = sf::Color(30, 144, 255);  // Dodger Blue

    // Main container
    float containerWidth = 500 * scale;
    float containerHeight = 500 * scale;
    sf::RectangleShape container(sf::Vector2f(containerWidth, containerHeight));
    container.setPosition((desktop.width - containerWidth) / 2, (desktop.height - containerHeight) / 2);
    container.setFillColor(sf::Color(255, 255, 255, 220)); // Semi-transparent white
    container.setOutlineThickness(2 * scale);
    container.setOutlineColor(sf::Color(255, 255, 255, 150));

    // Add subtle shadow effect
    sf::RectangleShape shadow(sf::Vector2f(containerWidth + 20 * scale, containerHeight + 20 * scale));
    shadow.setPosition(container.getPosition().x - 10 * scale, container.getPosition().y - 10 * scale);
    shadow.setFillColor(sf::Color(0, 0, 0, 50));

    // Header text
    sf::Text header("LOGIN", font, 40 * scale);
    header.setFillColor(sf::Color(25, 25, 112)); // Midnight Blue
    header.setStyle(sf::Text::Bold);
    sf::FloatRect headerBounds = header.getLocalBounds();
    header.setPosition((desktop.width - headerBounds.width) / 2, container.getPosition().y + 30 * scale);

    // Subheader text
    sf::Text subheader(" Hospital Management System", font, 24 * scale);
    subheader.setFillColor(sf::Color(105, 105, 105)); // Dim Gray
    sf::FloatRect subheaderBounds = subheader.getLocalBounds();
    subheader.setPosition((desktop.width - subheaderBounds.width) / 2, header.getPosition().y + headerBounds.height + 10 * scale);

    // Hospital icon (using SFML CircleShape for a simple icon)
    sf::CircleShape icon(40 * scale, 6); // Hexagon shape
    icon.setFillColor(sf::Color(25, 25, 112, 200)); // Midnight Blue with transparency
    icon.setOutlineThickness(2 * scale);
    icon.setOutlineColor(sf::Color(255, 255, 255, 200));
    icon.setPosition((desktop.width - icon.getRadius() * 2) / 2, header.getPosition().y - 80 * scale);

    // Plus sign inside icon
    sf::Text plusSign("+", font, 50 * scale);
    plusSign.setFillColor(sf::Color::White);
    sf::FloatRect plusBounds = plusSign.getLocalBounds();
    plusSign.setPosition(icon.getPosition().x + icon.getRadius() - plusBounds.width / 2,
        icon.getPosition().y + icon.getRadius() - plusBounds.height);

    // Username field
    sf::Text usernameLabel("Username:", font, 22 * scale);
    usernameLabel.setFillColor(sf::Color(70, 70, 70));
    usernameLabel.setPosition(container.getPosition().x + 50 * scale, container.getPosition().y + 120 * scale);

    sf::RectangleShape usernameBox(sf::Vector2f(400 * scale, 40 * scale));
    usernameBox.setPosition(usernameLabel.getPosition().x, usernameLabel.getPosition().y + 35 * scale);
    usernameBox.setFillColor(sf::Color(245, 245, 245));
    usernameBox.setOutlineThickness(1.5f * scale);
    usernameBox.setOutlineColor(sf::Color(200, 200, 200));

    sf::Text usernameInput("", font, 22 * scale);
    usernameInput.setFillColor(sf::Color::Black);
    usernameInput.setPosition(usernameBox.getPosition().x + 10 * scale, usernameBox.getPosition().y + 5 * scale);

    // Password field
    sf::Text passwordLabel("Password:", font, 22 * scale);
    passwordLabel.setFillColor(sf::Color(70, 70, 70));
    passwordLabel.setPosition(usernameLabel.getPosition().x, usernameBox.getPosition().y + 60 * scale);

    sf::RectangleShape passwordBox(sf::Vector2f(400 * scale, 40 * scale));
    passwordBox.setPosition(passwordLabel.getPosition().x, passwordLabel.getPosition().y + 35 * scale);
    passwordBox.setFillColor(sf::Color(245, 245, 245));
    passwordBox.setOutlineThickness(1.5f * scale);
    passwordBox.setOutlineColor(sf::Color(200, 200, 200));

    sf::Text passwordInput("", font, 22 * scale);
    passwordInput.setFillColor(sf::Color::Black);
    passwordInput.setPosition(passwordBox.getPosition().x + 10 * scale, passwordBox.getPosition().y + 5 * scale);

    // Login button
    sf::RectangleShape loginButton(sf::Vector2f(150 * scale, 45 * scale));
    loginButton.setPosition((desktop.width - loginButton.getSize().x) / 2, passwordBox.getPosition().y + 80 * scale);
    loginButton.setFillColor(sf::Color(30, 144, 255)); // Dodger Blue
    loginButton.setOutlineThickness(1.0f * scale);
    loginButton.setOutlineColor(sf::Color(25, 25, 112)); // Midnight Blue

    sf::Text loginButtonText("LOGIN", font, 24 * scale);
    loginButtonText.setFillColor(sf::Color::White);
    loginButtonText.setStyle(sf::Text::Bold);
    sf::FloatRect loginButtonBounds = loginButtonText.getLocalBounds();
    loginButtonText.setPosition(loginButton.getPosition().x + (loginButton.getSize().x - loginButtonBounds.width) / 2,
        loginButton.getPosition().y + (loginButton.getSize().y - loginButtonBounds.height) / 2 - 5 * scale);

    // Status message
    sf::Text messageText("", font, 20 * scale);
    messageText.setFillColor(sf::Color(220, 20, 60)); // Crimson

    // Footer
    sf::Text footer("Hospital Management System © 2025", font, 18 * scale);
    footer.setFillColor(sf::Color(255, 255, 255, 150));
    footer.setPosition((desktop.width - footer.getLocalBounds().width) / 2, desktop.height - 40 * scale);

    // Cursor for text input
    sf::RectangleShape cursor(sf::Vector2f(2 * scale, 25 * scale));
    cursor.setFillColor(sf::Color::Black);
    bool showCursor = false;
    sf::Clock cursorClock;

    while (window.isOpen() && attempts < MAX_ATTEMPTS) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return false;
                }
                if (event.key.code == sf::Keyboard::Tab) {
                    usernameActive = !usernameActive;
                    passwordActive = !passwordActive;
                    usernameBox.setOutlineColor(usernameActive ? sf::Color(30, 144, 255) : sf::Color(200, 200, 200));
                    passwordBox.setOutlineColor(passwordActive ? sf::Color(30, 144, 255) : sf::Color(200, 200, 200));
                    cursorClock.restart();
                    showCursor = true;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    // Check if clicked on username box
                    if (usernameBox.getGlobalBounds().contains(mousePos)) {
                        usernameActive = true;
                        passwordActive = false;
                        usernameBox.setOutlineColor(sf::Color(30, 144, 255)); // Dodger Blue
                        passwordBox.setOutlineColor(sf::Color(200, 200, 200));
                        cursorClock.restart();
                        showCursor = true;
                    }
                    // Check if clicked on password box
                    else if (passwordBox.getGlobalBounds().contains(mousePos)) {
                        passwordActive = true;
                        usernameActive = false;
                        passwordBox.setOutlineColor(sf::Color(30, 144, 255)); // Dodger Blue
                        usernameBox.setOutlineColor(sf::Color(200, 200, 200));
                        cursorClock.restart();
                        showCursor = true;
                    }
                    // Check if clicked on login button
                    else if (loginButton.getGlobalBounds().contains(mousePos)) {
                        if (username == "bahria" && password == "1234") {
                            messageText.setString("Login successful! Welcome to the system.");
                            messageText.setFillColor(sf::Color(34, 139, 34)); // Forest Green
                            sf::FloatRect messageBounds = messageText.getLocalBounds();
                            messageText.setPosition((desktop.width - messageBounds.width) / 2,
                                loginButton.getPosition().y + loginButton.getSize().y + 20 * scale);
                            window.clear();
                            window.draw(background);
                            window.draw(shadow);
                            window.draw(container);
                            window.draw(header);
                            window.draw(subheader);
                            window.draw(icon);
                            window.draw(plusSign);
                            window.draw(usernameLabel);
                            window.draw(usernameBox);
                            window.draw(usernameInput);
                            window.draw(passwordLabel);
                            window.draw(passwordBox);
                            window.draw(passwordInput);
                            window.draw(loginButton);
                            window.draw(loginButtonText);
                            window.draw(messageText);
                            window.draw(footer);
                            window.display();
                            sf::sleep(sf::seconds(1));
                            window.close();
                            return true;
                        }
                        else {
                            attempts++;
                            if (attempts < MAX_ATTEMPTS) {
                                messageText.setString("Invalid credentials. Attempts left: " + to_string(MAX_ATTEMPTS - attempts));
                            }
                            else {
                                messageText.setString("Maximum attempts reached. System will exit.");
                            }
                            messageText.setFillColor(sf::Color(220, 20, 60)); // Crimson
                            sf::FloatRect messageBounds = messageText.getLocalBounds();
                            messageText.setPosition((desktop.width - messageBounds.width) / 2,
                                loginButton.getPosition().y + loginButton.getSize().y + 20 * scale);
                        }
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char c = static_cast<char>(event.text.unicode);
                    if (c == '\r') { // Enter key
                        if (username == "bahria" && password == "1234") {
                            messageText.setString("Login successful! Welcome to the system.");
                            messageText.setFillColor(sf::Color(34, 139, 34)); // Forest Green
                            sf::FloatRect messageBounds = messageText.getLocalBounds();
                            messageText.setPosition((desktop.width - messageBounds.width) / 2,
                                loginButton.getPosition().y + loginButton.getSize().y + 20 * scale);
                            window.clear();
                            window.draw(background);
                            window.draw(shadow);
                            window.draw(container);
                            window.draw(header);
                            window.draw(subheader);
                            window.draw(icon);
                            window.draw(plusSign);
                            window.draw(usernameLabel);
                            window.draw(usernameBox);
                            window.draw(usernameInput);
                            window.draw(passwordLabel);
                            window.draw(passwordBox);
                            window.draw(passwordInput);
                            window.draw(loginButton);
                            window.draw(loginButtonText);
                            window.draw(messageText);
                            window.draw(footer);
                            window.display();
                            sf::sleep(sf::seconds(1));
                            window.close();
                            return true;
                        }
                        else {
                            attempts++;
                            if (attempts < MAX_ATTEMPTS) {
                                messageText.setString("Invalid credentials. Attempts left: " + to_string(MAX_ATTEMPTS - attempts));
                            }
                            else {
                                messageText.setString("Maximum attempts reached. System will exit.");
                            }
                            messageText.setFillColor(sf::Color(220, 20, 60)); // Crimson
                            sf::FloatRect messageBounds = messageText.getLocalBounds();
                            messageText.setPosition((desktop.width - messageBounds.width) / 2,
                                loginButton.getPosition().y + loginButton.getSize().y + 20 * scale);
                        }
                    }
                    else if (c == '\b') { // Backspace
                        if (usernameActive && !username.empty()) {
                            username.pop_back();
                            usernameInput.setString(username);
                        }
                        else if (passwordActive && !password.empty()) {
                            password.pop_back();
                            passwordInput.setString(string(password.length(), '*'));
                        }
                    }
                    else if (c >= 32 && c <= 126) { // Printable ASCII
                        if (usernameActive && username.length() < 20) {
                            username += c;
                            usernameInput.setString(username);
                        }
                        else if (passwordActive && password.length() < 20) {
                            password += c;
                            passwordInput.setString(string(password.length(), '*'));
                        }
                    }
                    cursorClock.restart();
                    showCursor = true;
                }
            }
        }

        // Cursor blinking
        if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        // Update button hover effect
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (loginButton.getGlobalBounds().contains(mousePos)) {
            loginButton.setFillColor(sf::Color(70, 130, 180)); // Light Steel Blue
        }
        else {
            loginButton.setFillColor(sf::Color(30, 144, 255)); // Dodger Blue
        }

        // Draw everything
        window.clear();
        window.draw(background);
        window.draw(shadow);
        window.draw(container);
        window.draw(header);
        window.draw(subheader);
        window.draw(icon);
        window.draw(plusSign);
        window.draw(usernameLabel);
        window.draw(usernameBox);
        window.draw(usernameInput);
        window.draw(passwordLabel);
        window.draw(passwordBox);
        window.draw(passwordInput);

        // Draw cursor if active and visible
        if (showCursor) {
            if (usernameActive) {
                cursor.setPosition(usernameInput.getPosition().x + usernameInput.getLocalBounds().width + 2 * scale,
                    usernameInput.getPosition().y);
                window.draw(cursor);
            }
            else if (passwordActive) {
                cursor.setPosition(passwordInput.getPosition().x + passwordInput.getLocalBounds().width + 2 * scale,
                    passwordInput.getPosition().y);
                window.draw(cursor);
            }
        }

        window.draw(loginButton);
        window.draw(loginButtonText);
        window.draw(messageText);
        window.draw(footer);
        window.display();
    }

    return false;
}

// Implementation for Person
void Person::getInfo() {
    SetConsoleTextAttribute(h, 6);
    cout << "Enter ID: ";
    cin >> id;
    cin.ignore(1000, '\n');
    do {
        cout << "Enter Name: ";
        getline(cin, name);
        if (name.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Name cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (name.empty());
    cout << "Enter Age: ";
    string input;
    int temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stoi(input);
                if (temp >= 1 && temp <= 150) {
                    age = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid age (1-150).\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Age: ";
    }
    do {
        cout << "Enter Gender: ";
        getline(cin, gender);
        if (gender.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Gender cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (gender.empty());
}

void Person::saveToFile(const string& filename, const string& type, const string& extraInfo) const {
    ofstream fout(filename, ios::app);
    if (!fout) {
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Could not open file " << filename << " for writing. Please check permissions.\n";
        SetConsoleTextAttribute(h, 3);
        cout << "Press Enter to retry or Esc to skip saving...";
        int c = cin.get();
        if (c == 27) { // Esc key
            return;
        }
        fout.open(filename, ios::app); // Retry
        if (!fout) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Failed to save record to " << filename << ".\n";
            return;
        }
    }
    fout << type << "," << id << "," << name << "," << age << "," << gender << "," << extraInfo << "\n";
    fout.close();
}

// Patient methods
void Patient::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Disease: ";
        getline(cin, disease);
        if (disease.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Disease cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (disease.empty());
    do {
        cout << "Enter Admission Date: ";
        getline(cin, admitDate);
        if (admitDate.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Admission Date cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (admitDate.empty());
}

void Patient::saveToFile() const {
    Person::saveToFile("patients.txt", "Patient", disease + "," + admitDate);
    SetConsoleTextAttribute(h, 2);
    cout << "\nPatient record saved to patients.txt\n";
}

// Doctor methods
void Doctor::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Department: ";
        getline(cin, department);
        if (department.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Department cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (department.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void Doctor::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("doctors.txt", "Doctor", "Department:" + department + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nDoctor record saved to doctors.txt\n";
}

// SpecialistDoctor methods
void SpecialistDoctor::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Specialty: ";
        getline(cin, specialty);
        if (specialty.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Specialty cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (specialty.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void SpecialistDoctor::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("specialist_doctors.txt", "SpecialistDoctor", "Specialization:" + specialty + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nSpecialist Doctor record saved to specialist_doctors.txt\n";
}

// Nurse methods
void Nurse::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Shift: ";
        getline(cin, shift);
        if (shift.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Shift cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (shift.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void Nurse::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("nurses.txt", "Nurse", "Shift:" + shift + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nNurse record saved to nurses.txt\n";
}

// CateringStaff methods
void CateringStaff::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Role: ";
        getline(cin, role);
        if (role.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Role cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (role.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void CateringStaff::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("catering_staff.txt", "CateringStaff", "Role:" + role + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nCatering staff record saved to catering_staff.txt\n";
}

// Receptionist methods
void Receptionist::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Shift: ";
        getline(cin, shift);
        if (shift.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Shift cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (shift.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void Receptionist::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("receptionists.txt", "Receptionist", "Shift:" + shift + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nReceptionist record saved to receptionists.txt\n";
}

// SecurityGuard methods
void SecurityGuard::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Duty Hours: ";
        getline(cin, dutyHours);
        if (dutyHours.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Duty Hours cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (dutyHours.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void SecurityGuard::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("security_guards.txt", "SecurityGuard", "Duty_hours:" + dutyHours + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nSecurity Guard record saved to security_guards.txt\n";
}

// Driver methods
void Driver::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter License Number: ";
        getline(cin, licenseNo);
        if (licenseNo.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: License Number cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (licenseNo.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void Driver::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("drivers.txt", "Driver", "License_no:" + licenseNo + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nDriver record saved to drivers.txt\n";
}

// Cleaner methods
void Cleaner::getInfo() {
    Person::getInfo();
    do {
        cout << "Enter Duty Hours: ";
        getline(cin, dutyHours);
        if (dutyHours.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Duty Hours cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (dutyHours.empty());
    cout << "Enter Salary: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    salary = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Salary: ";
    }
}

void Cleaner::saveToFile() const {
    stringstream ss;
    ss << salary;
    Person::saveToFile("cleaners.txt", "Cleaner", "Duty_hours:" + dutyHours + ",Salary:" + ss.str());
    SetConsoleTextAttribute(h, 2);
    cout << "\nCleaner record saved to cleaners.txt\n";
}

// Ambulance methods
void Ambulance::getInfo() {
    SetConsoleTextAttribute(h, 6);
    cin.ignore(1000, '\n'); // Clear any leftover newline
    cout << "Enter Vehicle No: ";
    cin >> vehicleNo;
    cin.ignore(1000, '\n');
    do {
        cout << "Enter Model: ";
        getline(cin, model);
        if (model.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Model cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (model.empty());
    do {
        cout << "Enter Driver Name: ";
        getline(cin, driverName);
        if (driverName.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Driver Name cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 6);
        }
    } while (driverName.empty());
    cout << "Enter Petrol Price: ";
    string input;
    float temp;
    while (true) {
        getline(cin, input);
        bool valid = true;
        bool hasDecimal = false;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (c == '.' && !hasDecimal) hasDecimal = true;
            else if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                temp = stof(input);
                if (temp >= 0) {
                    petrol_price = temp;
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter a valid non-negative number.\n";
        SetConsoleTextAttribute(h, 6);
        cout << "Enter Petrol Price: ";
    }
}

void Ambulance::saveToFile() const {
    ofstream fout("ambulances.txt", ios::app);
    if (!fout) {
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Could not open file ambulances.txt for writing. Please check permissions.\n";
        SetConsoleTextAttribute(h, 3);
        cout << "Press Enter to retry or Esc to skip saving...";
        int c = cin.get();
        if (c == 27) { // Esc key
            return;
        }
        fout.open("ambulances.txt", ios::app); // Retry
        if (!fout) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Failed to save record to ambulances.txt.\n";
            return;
        }
    }
    stringstream ss;
    ss << petrol_price;
    fout << "Ambulance," << vehicleNo << "," << model << "," << driverName << "," << ss.str() << "\n";
    fout.close();
    SetConsoleTextAttribute(h, 2);
    cout << "\nAmbulance record saved to ambulances.txt\n";
}

void displayFormattedRecords(const string& filename, const string& type) {
    ifstream fin(filename);
    if (!fin) {
        SetConsoleTextAttribute(h, 4);
        cout << "No records found for " << type << ".\n";
        return;
    }
    SetConsoleTextAttribute(h, 1);
    cout << "\n=============================================\n";
    cout << "           " << type << " RECORDS\n";
    cout << "=============================================\n";
    cout << left << setw(8) << "ID" << setw(20) << "Name"
        << setw(6) << "Age" << setw(8) << "Gender" << "Details\n";
    cout << "------------------------------------------------\n";
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string token;
        int col = 0;
        while (getline(ss, token, ',')) {
            if (col == 1) cout << left << setw(8) << token;
            else if (col == 2) cout << left << setw(20) << token;
            else if (col == 3) cout << left << setw(6) << token;
            else if (col == 4) cout << left << setw(8) << token;
            else if (col >= 5) cout << token << " ";
            col++;
        }
        cout << endl;
    }
    fin.close();
}

void searchRecord(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        SetConsoleTextAttribute(h, 4);
        cout << "File not found!\n";
        return;
    }

    int searchChoice;
    string keyword;
    string type = filename.substr(0, filename.find('.'));
    transform(type.begin(), type.end(), type.begin(), ::toupper);
    SetConsoleTextAttribute(h, 3);
    cout << "Search by:\n1. ID\n2. Name\nEnter choice: ";
    string input;
    while (true) {
        getline(cin, input);
        bool valid = true;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                searchChoice = stoi(input);
                if (searchChoice == 1 || searchChoice == 2) {
                    break;
                }
            }
            catch (...) {
                valid = false;
            }
        }
        SetConsoleTextAttribute(h, 4);
        cout << "Error: Enter 1 or 2.\n";
        SetConsoleTextAttribute(h, 3);
        cout << "Enter choice: ";
    }
    do {
        cout << "Enter keyword: ";
        getline(cin, keyword);
        if (keyword.empty()) {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Keyword cannot be empty. Please try again.\n";
            SetConsoleTextAttribute(h, 3);
        }
    } while (keyword.empty());

    string keywordLower = keyword;
    transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

    bool found = false;
    vector<string> matchingRecords;
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() < 3) continue;

        string idLower = tokens[1];
        string nameLower = tokens[2];
        transform(idLower.begin(), idLower.end(), idLower.begin(), ::tolower);
        transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);

        if ((searchChoice == 1 && idLower.find(keywordLower) != string::npos) ||
            (searchChoice == 2 && nameLower.find(keywordLower) != string::npos)) {
            matchingRecords.push_back(line);
            found = true;
        }
    }
    fin.close();

    if (!found) {
        SetConsoleTextAttribute(h, 4);
        cout << "No matching record found.\n";
        return;
    }

    SetConsoleTextAttribute(h, 1);
    cout << "\n=============================================\n";
    cout << "           " << type << " SEARCH RESULTS\n";
    cout << "=============================================\n";
    cout << left << setw(8) << "ID" << setw(20) << "Name"
        << setw(6) << "Age" << setw(8) << "Gender" << "Details\n";
    cout << "------------------------------------------------\n";
    for (const string& record : matchingRecords) {
        stringstream ss(record);
        string token;
        int col = 0;
        while (getline(ss, token, ',')) {
            if (col == 1) cout << left << setw(8) << token;
            else if (col == 2) cout << left << setw(20) << token;
            else if (col == 3) cout << left << setw(6) << token;
            else if (col == 4) cout << left << setw(8) << token;
            else if (col >= 5) cout << token << " ";
            col++;
        }
        cout << endl;
    }
}

void showMenu() {
    SetConsoleTextAttribute(h, 2);
    cout << "\n=============================================\n";
    cout << "       HOSPITAL MANAGEMENT SYSTEM MENU        \n";
    cout << "=============================================\n";
    SetConsoleTextAttribute(h, 6);
    cout << "1. Add Patient\n2. Add Doctor\n3. Add Specialist Doctor\n4. Add Nurse\n";
    cout << "5. Add Catering Staff\n6. Add Receptionist\n7. Add Security Guard\n";
    cout << "8. Add Driver\n9. Add Cleaner\n10. Add Ambulance\n";
    cout << "11. Display Records\n12. Search Record\n0. Exit\n";
    SetConsoleTextAttribute(h, 3);
    cout << "Enter your choice: ";
}

int main() {
    if (h == INVALID_HANDLE_VALUE) {
        cout << "Error: Unable to get console handle.\n";
        return 1;
    }

    if (!login()) return 1;

    int choice;
    do {
        showMenu();
        string input;
        getline(cin, input);
        bool valid = true;
        if (input.empty()) valid = false;
        for (char c : input) {
            if (!isdigit(c)) valid = false;
        }
        if (valid) {
            try {
                choice = stoi(input);
                if (choice >= 0 && choice <= 12) {
                    switch (choice) {
                    case 1: { Patient p; p.getInfo(); p.saveToFile(); break; }
                    case 2: { Doctor d; d.getInfo(); d.saveToFile(); break; }
                    case 3: { SpecialistDoctor sd; sd.getInfo(); sd.saveToFile(); break; }
                    case 4: { Nurse n; n.getInfo(); n.saveToFile(); break; }
                    case 5: { CateringStaff c; c.getInfo(); c.saveToFile(); break; }
                    case 6: { Receptionist r; r.getInfo(); r.saveToFile(); break; }
                    case 7: { SecurityGuard sg; sg.getInfo(); sg.saveToFile(); break; }
                    case 8: { Driver d; d.getInfo(); d.saveToFile(); break; }
                    case 9: { Cleaner c; c.getInfo(); c.saveToFile(); break; }
                    case 10: { Ambulance a; a.getInfo(); a.saveToFile(); break; }
                    case 11: {
                        cout << "Which record do you want to display?\n1. Patient\n2. Doctor\n3. Specialist Doctor\n4. Nurse\n5. Catering Staff\n6. Receptionist\n7. Security Guard\n8. Driver\n9. Cleaner\n10. Ambulance\n";
                        int subChoice;
                        string input;
                        getline(cin, input);
                        bool valid = true;
                        if (input.empty()) valid = false;
                        for (char c : input) {
                            if (!isdigit(c)) valid = false;
                        }
                        if (valid) {
                            try {
                                subChoice = stoi(input);
                                if (subChoice >= 1 && subChoice <= 10) {
                                    switch (subChoice) {
                                    case 1: displayFormattedRecords("patients.txt", "Patient"); break;
                                    case 2: displayFormattedRecords("doctors.txt", "Doctor"); break;
                                    case 3: displayFormattedRecords("specialist_doctors.txt", "Specialist Doctor"); break;
                                    case 4: displayFormattedRecords("nurses.txt", "Nurse"); break;
                                    case 5: displayFormattedRecords("catering_staff.txt", "Catering Staff"); break;
                                    case 6: displayFormattedRecords("receptionists.txt", "Receptionist"); break;
                                    case 7: displayFormattedRecords("security_guards.txt", "Security Guard"); break;
                                    case 8: displayFormattedRecords("drivers.txt", "Driver"); break;
                                    case 9: displayFormattedRecords("cleaners.txt", "Cleaner"); break;
                                    case 10: displayFormattedRecords("ambulances.txt", "Ambulance"); break;
                                    }
                                }
                                else {
                                    SetConsoleTextAttribute(h, 4);
                                    cout << "Error: Choice must be between 1 and 10.\n";
                                }
                            }
                            catch (...) {
                                SetConsoleTextAttribute(h, 4);
                                cout << "Error: Enter a valid number.\n";
                            }
                        }
                        else {
                            SetConsoleTextAttribute(h, 4);
                            cout << "Error: Enter a valid number.\n";
                        }
                        break;
                    }
                    case 12: {
                        cout << "Search in which file?\n1. patients.txt\n2. doctors.txt\n3. specialist_doctors.txt\n4. nurses.txt\n5. catering_staff.txt\n6. receptionists.txt\n7. security_guards.txt\n8. drivers.txt\n9. cleaners.txt\n10. ambulances.txt\n";
                        int subChoice;
                        string input;
                        getline(cin, input);
                        bool valid = true;
                        if (input.empty()) valid = false;
                        for (char c : input) {
                            if (!isdigit(c)) valid = false;
                        }
                        if (valid) {
                            try {
                                subChoice = stoi(input);
                                if (subChoice >= 1 && subChoice <= 10) {
                                    string filename;
                                    switch (subChoice) {
                                    case 1: filename = "patients.txt"; break;
                                    case 2: filename = "doctors.txt"; break;
                                    case 3: filename = "specialist_doctors.txt"; break;
                                    case 4: filename = "nurses.txt"; break;
                                    case 5: filename = "catering_staff.txt"; break;
                                    case 6: filename = "receptionists.txt"; break;
                                    case 7: filename = "security_guards.txt"; break;
                                    case 8: filename = "drivers.txt"; break;
                                    case 9: filename = "cleaners.txt"; break;
                                    case 10: filename = "ambulances.txt"; break;
                                    }
                                    searchRecord(filename);
                                }
                                else {
                                    SetConsoleTextAttribute(h, 4);
                                    cout << "Error: Choice must be between 1 and 10.\n";
                                }
                            }
                            catch (...) {
                                SetConsoleTextAttribute(h, 4);
                                cout << "Error: Enter a valid number.\n";
                            }
                        }
                        else {
                            SetConsoleTextAttribute(h, 4);
                            cout << "Error: Enter a valid number.\n";
                        }
                        break;
                    }
                    case 0: SetConsoleTextAttribute(h, 2); cout << "Exiting...\n"; break;
                    }
                }
                else {
                    SetConsoleTextAttribute(h, 4);
                    cout << "Error: Choice must be between 0 and 12.\n";
                }
            }
            catch (...) {
                SetConsoleTextAttribute(h, 4);
                cout << "Error: Enter a valid number.\n";
            }
        }
        else {
            SetConsoleTextAttribute(h, 4);
            cout << "Error: Enter a valid number.\n";
        }
        pause();
        system("cls");
    } while (choice != 0);

    return 0;
}