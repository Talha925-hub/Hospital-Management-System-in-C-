# 🏥 Hospital Management System

A comprehensive **C++ application** for managing hospital operations with GUI login and console-based record management using Object-Oriented design principles.

## ✨ Features

- **Secure Login System**: GUI-based authentication with user credentials
- **Staff Management**: Add, search, and manage staff records with roles
- **Patient Management**: Track patient information, medical history, and appointments
- **Ambulance Management**: Monitor ambulance availability and assignments
- **Advanced Search**: Quick search functionality across all records
- **Data Validation**: Comprehensive input validation for data integrity
- **File Storage**: Persistent storage using text files (.txt)
- **Multiple User Roles**: Different access levels for admin, staff, and patients
- **Menu-Driven Interface**: Intuitive navigation with formatted output
- **Color Console**: Enhanced UI with colored text for better readability

## 🛠️ Tech Stack

- **Language**: C++
- **GUI Framework**: SFML (for login interface)
- **Architecture**: Object-Oriented Programming (OOP)
- **Database**: File-based storage (.txt files)
- **UI Style**: Console-based with color support

## 📋 Prerequisites

- C++ compiler (C++11 or higher)
- SFML library installed (for GUI login)
- Windows/Linux/MacOS

## 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/Talha925-hub/Hospital-Management-System-in-C-.git
cd Hospital-Management-System-in-C-

# Compile the application
g++ -c main.cpp -o main.o
g++ main.o -o hospital_system -lsfml-graphics -lsfml-window -lsfml-system

# Run the application
./hospital_system
```

## 📖 Usage

### 1. **Login Screen** (GUI)
- Enter username and password
- Different roles available: Admin, Doctor, Nurse, Receptionist

### 2. **Staff Module**
```
- Add new staff member
- View all staff
- Search staff by ID
- Update staff information
- Delete staff record
```

### 3. **Patient Module**
```
- Register new patient
- View patient records
- Search by patient ID/name
- Update patient information
- View medical history
- Schedule appointments
```

### 4. **Ambulance Module**
```
- View ambulance fleet
- Track ambulance status
- Assign ambulance to cases
- Manage driver information
```

## 🎯 Project Structure

```
Hospital-Management-System-in-C-/
├── main.cpp                 # Main application entry
├── login.h / login.cpp      # Authentication system
├── staff.h / staff.cpp      # Staff management
├── patient.h / patient.cpp  # Patient records
├── ambulance.h / ambulance.cpp  # Ambulance management
├── utilities.h / utilities.cpp  # Helper functions
├── data/                    # Storage directory
│   ├── staff.txt
│   ├── patients.txt
│   └── ambulance.txt
└── README.md
```

## 🏗️ Class Hierarchy

```
Hospital Management System
├── Staff
│   ├── Doctor
│   ├── Nurse
│   └── Receptionist
├── Patient
│   ├── Personal Info
│   ├── Medical History
│   └── Appointments
└── Ambulance
    ├── Driver Info
    ├── Vehicle Details
    └── Status
```

## 🔐 Security Features

- User authentication with encrypted passwords
- Role-based access control
- Audit trails for sensitive operations
- Data validation at input points

## 💾 Data Persistence

All records are automatically saved to text files:
- **staff.txt** - Staff information
- **patients.txt** - Patient records
- **ambulance.txt** - Ambulance fleet data

```
Sample Staff Record:
---
ID: S001
Name: Dr. Ahmed Hassan
Position: Doctor
Department: Cardiology
Contact: 03001234567
Joining Date: 2025-01-15
Status: Active
```

## 🎮 Sample Workflow

```
1. Login as Admin
2. Add new staff member
3. Register patient
4. Schedule appointment
5. Manage ambulance dispatch
6. Generate reports
```

## 🔧 Customization Options

- Add more user roles
- Implement appointment scheduling
- Add medical history tracking
- Create billing module
- Add prescription management
- Implement lab test records

## 📊 Functions Overview

| Module | Operations |
|--------|-----------|
| Staff | CRUD, Search, Filter |
| Patient | Register, View, Update, History |
| Ambulance | Track, Assign, Status |
| Login | Authenticate, Authorize |

## 🐛 Known Issues

- Console color support varies across platforms
- File-based storage has size limitations
- No concurrent user handling

## 📈 Future Enhancements

- [ ] Database migration (MySQL/PostgreSQL)
- [ ] Web-based dashboard
- [ ] Mobile app integration
- [ ] Telemedicine support
- [ ] Prescription management
- [ ] Billing and invoicing
- [ ] Online appointment booking
- [ ] Medical records with encryption
- [ ] SMS notifications
- [ ] Real-time tracking

## 📄 License

This project is open source and available under the MIT License.

## 👨‍💻 Author

**Talha925-hub** - Software developer specializing in C++ and healthcare management systems

## 📞 Support

- GitHub: [@Talha925-hub](https://github.com/Talha925-hub)
- Issues: [Create an issue](https://github.com/Talha925-hub/Hospital-Management-System-in-C-/issues)
- Suggestions: Feel free to contribute!

## 🤝 Contributing

Contributions are welcome! Please fork the repository and submit pull requests with improvements.

---

⭐ **Found this useful? Please star the repository and share it with others!**
