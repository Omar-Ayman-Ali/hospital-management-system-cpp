# 🏥 Hospital Management System

A console-based Hospital Management System built in **C++** featuring multi-role authentication, appointment scheduling, doctor availability management, and persistent file-based data storage.

> Built as a collaborative team project in C++.

---

## ✨ Features

### 👤 Patient
- Sign up with phone number validation (digits-only, unique)
- Login with ID and password
- Book appointments with availability checking
- View personal appointment history
- Cancel existing appointments
- Browse all registered doctors

### 🩺 Doctor
- Secure login with doctor ID and password
- View full appointment schedule
- Update availability (date range + working hours)
- Set consultation fee

### 🔐 Admin
- Login with name and password
- Add / remove doctors
- View all system appointments
- Edit any doctor's consultation fee

---

## 🗂️ Project Structure

```
hospital-management-system-cpp/
│
├── Team3.cpp       # Full source code (single-file)
├── README.md
│
# Generated at runtime:
├── doctors.txt     # Persisted doctor data
├── patients.txt    # Persisted patient data
└── appointments.txt# Persisted appointment data
```

---

## ⚙️ How It Works

### Availability Validation
When booking an appointment, the system checks:
1. **Day of week** — uses [Zeller's Congruence](https://en.wikipedia.org/wiki/Zeller%27s_congruence) to compute the weekday from any date
2. **Working hours** — validates the requested time is within the doctor's shift
3. **Slot conflict** — ensures no two active appointments share the same doctor + date + time

### Data Persistence
On exit, all data is written to plain-text files (`doctors.txt`, `patients.txt`, `appointments.txt`) and reloaded on next startup — no database required.

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler (GCC / G++ recommended)

### Build & Run

```bash
# Clone the repo
git clone https://github.com/Omar-Ayman-Ali/hospital-management-system-cpp.git
cd hospital-management-system-cpp

# Compile
g++ Team3.cpp -o hospital

# Run
./hospital
```

---

## 🔑 Default Credentials (seeded on first run)

| Role    | Name / ID       | Password   |
|---------|-----------------|------------|
| Admin   | Admin           | Admin      |
| Doctor  | ID: 1 (Dr. Ahmed Khalil) | ahmed123 |
| Doctor  | ID: 2 (Dr. Sara Mostafa) | sara123  |
| Doctor  | ID: 3 (Dr. Omar Hassan)  | omar123  |
| Patient | ID: 1 (Ali Mohamed)      | ali123   |
| Patient | ID: 2 (Nour Tarek)       | nour123  |

> ⚠️ Change passwords after first use for any real deployment.

---

## 📐 System Limits

| Resource     | Max Capacity |
|--------------|-------------|
| Doctors      | 20          |
| Patients     | 50          |
| Appointments | 100         |
| Admins       | 2           |

---

## 🛠️ Tech Stack

| Layer       | Technology          |
|-------------|---------------------|
| Language    | C++ (standard I/O)  |
| Storage     | File I/O (`fstream`)|
| Algorithm   | Zeller's Congruence |
| UI          | Console (CLI)       |

---


## 📄 License

This project is open source and available under the [MIT License](LICENSE).
