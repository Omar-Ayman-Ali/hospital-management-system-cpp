# Hospital Management System (C++ Console Application)

**Live Demo:** Not deployed (local execution only)

A single-file C++ console application for managing patients, doctors, and appointments through role-based menus, with data stored in plain-text files.

![Language](https://img.shields.io/badge/Language-C%2B%2B14-00599C?style=flat-square)
![Compiler](https://img.shields.io/badge/Compiler-GCC_%7C_Clang-lightgrey?style=flat-square)
![Interface](https://img.shields.io/badge/Interface-CLI-black?style=flat-square)
![Storage](https://img.shields.io/badge/Storage-Plain_Text_Files-orange?style=flat-square)
![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)

---

## Table of Contents
- [About](#about)
- [Architecture](#architecture)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Run Locally](#run-locally)
- [Project Structure](#project-structure)
- [License](#license)

---

## About
This project models the core workflows of a hospital front desk: patient registration, appointment booking, doctor scheduling, and staff administration. It is written in procedural C++ using only the standard library, with structs, fixed-size arrays, and file streams. It was built as a collaborative university team project and is an **educational implementation**, not a production system.

---

## Architecture

### Program Flow
`main()` seeds sample data with `initial()`, then calls `loadData()`, which replaces the seed data with the contents of the data files if they exist. A main menu routes the user to one of three role menus (Patient, Doctor, Admin). Each role authenticates, then enters its own menu loop. Choosing **Exit** from the main menu calls `saveData()` and ends the program.

### Data Model
All state lives in global, fixed-size arrays of structs (`patient`, `doctor`, `appointment`, `admin`). There is no dynamic allocation and no database.

| Resource     | Capacity |
|--------------|----------|
| Doctors      | 20       |
| Patients     | 50       |
| Appointments | 100      |
| Admins       | 2        |

### Appointment Validation
Before an appointment is booked, `isAvailable()` runs three checks:
1. **Weekday**: [Zeller's Congruence](https://en.wikipedia.org/wiki/Zeller%27s_congruence) converts the requested date to a weekday, which must be one of the doctor's work days.
2. **Working hours**: the requested time must fall within the doctor's daily start and end time.
3. **Slot conflict**: no non-cancelled appointment may exist for the same doctor, date, and time.

The booking cost is copied from the doctor's consultation fee at booking time, so later fee changes do not alter existing appointments.

### Persistence
Data is written to `doctors.txt`, `patients.txt`, and `appointments.txt` in the working directory. Files are only written on a clean exit through the main menu. Terminating the process any other way (for example, `Ctrl+C`) discards all changes made during the session.

### Known Limitations
- Passwords are stored and compared in **plain text**.
- The availability start and end **dates** a doctor sets are stored but not enforced. Only the weekday and time of day are checked.
- Patient and appointment IDs are derived from the current record count.
- There is no input length validation beyond numeric checks.

---

## Features
- **Patient Registration**: Sign up with a name, password, age, and a digits-only phone number that must be unique.
- **Appointment Booking**: Book a doctor by ID, date, and time, with weekday, working-hours, and conflict checks.
- **Appointment Management**: Patients can view their appointment history and cancel their own booked appointments.
- **Doctor Directory**: Browse all doctors with their specialization, work days, working hours, and fee.
- **Doctor Scheduling**: Doctors can view their appointments, update availability, and set their consultation fee.
- **Doctor Administration**: Admins can add doctors, remove doctors, and edit any doctor's fee.
- **Cascading Cancellation**: Removing a doctor cancels all of that doctor's open appointments.
- **System Overview**: Admins can view every appointment in the system.
- **File Persistence**: All records are saved on exit and reloaded on the next start.

---

## Tech Stack
- **Language**: C++14 (standard library only)
- **Libraries**: `<iostream>`, `<fstream>`, `<string>`, `<cctype>`
- **Storage**: Plain-text files via `std::fstream`
- **Interface**: Interactive console menus
- **Build Tooling**: Any C++14 compiler (GCC, Clang, or MSVC). No build system required.

---

## Run Locally

### Prerequisites
- A C++ compiler with **C++14** support, such as GCC >= 5 or Clang >= 3.4.

The code does not compile under C++11 because the `doctor` struct uses a default member initializer with aggregate initialization.

### Installation
```bash
git clone https://github.com/Omar-Ayman-Ali/hospital-management-system-cpp.git
cd hospital-management-system-cpp
g++ -std=c++14 MainCode.cpp -o hospital
```

### Execution
```bash
./hospital
```

On Windows, run `hospital.exe` instead.

On first run, the program starts with the following seed accounts. After the first clean exit, these are saved to the data files and loaded from there on later runs.

| Role    | Login                        | Password   |
|---------|------------------------------|------------|
| Admin   | Name: `Admin`                | `Admin`    |
| Doctor  | ID: `1` (Dr. Ahmed Khalil)   | `ahmed123` |
| Doctor  | ID: `2` (Dr. Sara Mostafa)   | `sara123`  |
| Doctor  | ID: `3` (Dr. Omar Hassan)    | `omar123`  |
| Patient | ID: `1` (Ali Mohamed)        | `ali123`   |
| Patient | ID: `2` (Nour Tarek)         | `nour123`  |

To reset all data to the seed state, delete the three `.txt` data files and start the program again.

---

## Project Structure
```text
.
├── MainCode.cpp        # Complete application source (single file)
├── LICENSE             # MIT License
└── README.md           # Project documentation

Generated at runtime in the working directory:
├── doctors.txt         # Doctor records and next doctor ID
├── patients.txt        # Patient records
└── appointments.txt    # Appointment records
```

---

## License
This project is available under the [MIT License](LICENSE).
