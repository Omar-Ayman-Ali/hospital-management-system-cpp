#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

const int daysize = 7;
string days[daysize] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};

struct duration
{
    int hour;
    int min;
};

struct date
{
    int year;
    int month;
    int day;
    int specificDay;
    duration time;
};

struct patient
{
    int patientId;
    string name;
    string password;
    string phoneNumber;
    int age;
};

struct doctor
{
    int doctorId;
    string name;
    int AvalableSlots[daysize] = {-1, -1, -1, -1, -1, -1, -1};
    string specialization;
    date begin;
    date end;
    double consultationFee;
    string password;
};

struct appointment
{
    int appointmentId;
    int doctorId;
    int patientId;
    date appointmentDate;
    duration appointmentTime;
    string status;
    double totalCost;
};

struct admin
{
    int adminId;
    string name;
    string password;
};

doctor doctors[20];
patient patients[50];
appointment appointments[100];
admin admins[2];
int doctorCount = 0;
int patientCount = 0;
int appointmentCount = 0;
int adminCount = 0;
const int max_doctor = 20;
const int max_patient = 50;
const int max_appointment = 100;
const int max_admin = 2;

int nextDoctorId = 1;
int getValidInteger();
void printWorkDays(int AvalableSlots[]);
void ViewAllAppointments();
void addDoctor();
void removeDoctor();
void cancelDoctorAppointments(int doctorId);
int adminLogin();
void setDoctorFee(int doctorId);
void adminMenu();
void adminMainMenu();
void viewDoctorSchedule(int doctorId);
void setDoctorAvailability(int doctorId);
void doctorMenu(int doctorId);
int Doctorlogin();
void doctorMainMenu();
bool isPhoneUsed(string phone);
void viewAppointments(int patientId);
bool IsDigit(string phone);
void signUp();
int zellersCongruence(int day, int month, int year);
int login();
string isAvailable(int doctorId, date appointmentDate, duration appointmentTime);
void bookAppointment(int id);
bool cancelAppointment(int appointmentId, int patientId);
void viewDoctors();
void internalMenu(int id);
void patientMenu();
void initial();
void saveData();
void loadData();

int main()
{
    initial();
    loadData();
    cout << "Welcome to the Hospital Management System!\n";
    int mainChoice;
    do
    {
        cout << "\n--- Main Menu ---\n"
             << "1. Patient\n"
             << "2. Doctor\n"
             << "3. Admin\n"
             << "4. Exit\n"
             << "Enter your choice: ";
        mainChoice = getValidInteger();

        switch (mainChoice)
        {
        case 1:
            patientMenu();
            break;
        case 2:
            doctorMainMenu();
            break;
        case 3:
            adminMainMenu();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (mainChoice != 4);
    saveData();
    return 0;
}
int getValidInteger()
{
    int number;

    while (!(cin >> number))
    {
        cout << "Invalid input! Please enter a valid number: ";

        cin.clear();

        cin.ignore(1000, '\n');
    }

    return number;
}
void printWorkDays(int AvalableSlots[])
{
    cout << "Work Days: ";
    for (int i = 0; i < daysize; i++)
    {
        if (AvalableSlots[i] != -1)
            cout << days[AvalableSlots[i]] << " ";
    }
    cout << endl;
}

void ViewAllAppointments()
{
    cout << "\n--- All Appointments ---\n";
    for (int i = 0; i < appointmentCount; i++)
    {
        cout << "Appointment ID: " << appointments[i].appointmentId << endl;
        cout << "Patient ID: " << appointments[i].patientId << endl;
        cout << "Doctor ID: " << appointments[i].doctorId << endl;
        cout << "Date: " << appointments[i].appointmentDate.year << "-"
             << appointments[i].appointmentDate.month << "-"
             << appointments[i].appointmentDate.day << endl;
        cout << "Time: " << appointments[i].appointmentTime.hour << ":"
             << appointments[i].appointmentTime.min << endl;
        cout << "Status: " << appointments[i].status << endl;
        cout << "Total Cost: $" << appointments[i].totalCost << endl;
        cout << "-----------------------------\n";
    }
}

void addDoctor()
{
    if (doctorCount >= max_doctor)
    {
        cout << "Doctor list is full!" << endl;
        return;
    }

    doctor newDoctor;
    newDoctor.doctorId = nextDoctorId++;
    cout << "\n--- Add Doctor ---\n";

    cout << "Enter doctor's name: ";
    cin.ignore();
    getline(cin, newDoctor.name);

    cout << "Enter doctor's specialization: ";
    getline(cin, newDoctor.specialization);

    cout << "Enter number of work days: ";
    int numDays;
    numDays = getValidInteger();
    if (numDays > daysize)
        numDays = daysize;
    cout << "Enter work day numbers (0=Sunday, 1=Monday, ..., 6=Saturday):\n";
    for (int i = 0; i < numDays; i++)
    {
        newDoctor.AvalableSlots[i] = getValidInteger();
    }

    cout << "Enter availability start date and time (YYYY MM DD HH MM): ";
    newDoctor.begin.year = getValidInteger();
    newDoctor.begin.month = getValidInteger();
    newDoctor.begin.day = getValidInteger();
    newDoctor.begin.time.hour = getValidInteger();
    newDoctor.begin.time.min = getValidInteger();

    cout << "Enter availability end date and time (YYYY MM DD HH MM): ";
    newDoctor.end.year = getValidInteger();
    newDoctor.end.month = getValidInteger();
    newDoctor.end.day = getValidInteger();
    newDoctor.end.time.hour = getValidInteger();
    newDoctor.end.time.min = getValidInteger();

    cout << "Enter doctor's consultation fee: $";
    newDoctor.consultationFee = getValidInteger();

    cout << "Enter doctor's password: ";
    cin.ignore();
    getline(cin, newDoctor.password);

    doctors[doctorCount] = newDoctor;
    doctorCount++;

    cout << "\nDoctor added successfully! Doctor ID is "
         << newDoctor.doctorId << endl;
}

void removeDoctor()
{
    int doctorId;
    cout << "\n--- Remove Doctor ---\n";
    cout << "Enter Doctor ID to remove: ";
    doctorId = getValidInteger();

    if (doctorId < 0)
    {
        cout << "Invalid doctor ID!\n";
        return;
    }

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == doctorId)
        {
            for (int j = i; j < doctorCount - 1; j++)
            {
                doctors[j] = doctors[j + 1];
            }
            doctorCount--;
            cancelDoctorAppointments(doctorId);
            cout << "Doctor removed successfully.\n";
            return;
        }
    }
    cout << "Doctor not found!\n";
}

void cancelDoctorAppointments(int doctorId)
{
    int cancelledCount = 0;
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].doctorId == doctorId &&
            appointments[i].status != "Cancelled" &&
            appointments[i].status != "Completed")
        {
            appointments[i].status = "Cancelled";
            cancelledCount++;
        }
    }
    if (cancelledCount > 0)
    {
        cout << cancelledCount << " appointment(s) cancelled for removed doctor." << endl;
    }
}

int adminLogin()
{
    string name, password;
    cin.ignore();
    cout << "\t Enter Your Name : \t" << endl;
    getline(cin, name);
    cout << "\t Enter Your Password : \t" << endl;
    getline(cin, password);
    for (int i = 0; i < adminCount; i++)
    {
        if (admins[i].name == name && admins[i].password == password)
        {
            cout << "\t Welcome " << name << endl;
            return admins[i].adminId;
        }
    }
    cout << "\t Password or Name is invalid \t" << "\n";
    return -1;
}

void setDoctorFee(int doctorId)
{
    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == doctorId)
        {
            cout << "Current Consultation Fee: $" << doctors[i].consultationFee << endl;
            cout << "Enter new Consultation Fee: $";
            doctors[i].consultationFee = getValidInteger();
            cout << "Doctor consultation fee updated successfully.\n";
            return;
        }
    }
    cout << "Doctor not found!\n";
}

void adminMenu()
{
    int choice;

    do
    {
        cout << "\n--- Admin Menu ---\n"
             << "1. Add Doctor\n"
             << "2. View Doctors\n"
             << "3. View All Appointments\n"
             << "4. Edit Doctor Consultation Fee\n"
             << "5. Remove Doctor\n"
             << "6. Logout\n";
        choice = getValidInteger();
        if (choice == 1)
        {
            addDoctor();
        }
        else if (choice == 2)
        {
            cout << "\n--- List of Doctors ---\n";
            for (int i = 0; i < doctorCount; i++)
            {
                cout << "Doctor ID: " << doctors[i].doctorId << endl
                     << "Name: " << doctors[i].name << endl
                     << "Specialization: " << doctors[i].specialization << endl
                     << "Consultation Fee: $" << doctors[i].consultationFee << endl
                     << "-----------------------------\n";
            }
        }
        else if (choice == 3)
            ViewAllAppointments();
        else if (choice == 4)
        {
            int Id;
            cout << "Enter Doctor ID: ";
            Id = getValidInteger();
            setDoctorFee(Id);
        }
        else if (choice == 5)
            removeDoctor();
        else if (choice == 6)
        {
            cout << "Logging out. Goodbye!\n";
            return;
        }
        else
            cout << "Invalid choice! Please try again.\n";
    } while (choice != 6);
}

void adminMainMenu()
{
    int choice;
    do
    {
        cout << "1. Login\n2. Exit\n";
        choice = getValidInteger();
        if (choice == 1)
        {
            int s = adminLogin();
            if (s != -1)
            {
                adminMenu();
            }
        }
        else if (choice == 2)
            return;
    } while (choice != 2);
}

void viewDoctorSchedule(int doctorId)
{
    cout << "\n---v Doctor Schedule ---\n";
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].doctorId == doctorId)
        {
            cout << "Appointment ID: " << appointments[i].appointmentId << endl;
            cout << "Patient ID: " << appointments[i].patientId << endl;
            cout << "Date: " << appointments[i].appointmentDate.year << "-"
                 << appointments[i].appointmentDate.month << "-"
                 << appointments[i].appointmentDate.day << endl;
            cout << "Time: " << appointments[i].appointmentTime.hour << ":"
                 << appointments[i].appointmentTime.min << endl;
            cout << "Status: " << appointments[i].status << endl;
            cout << "Total Cost: $" << appointments[i].totalCost << endl;
            cout << "-----------------------------\n";
        }
    }
}

void setDoctorAvailability(int doctorId)
{
    cout << "\n--- Set Doctor Availability ---\n";

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == doctorId)
        {
            cout << "Enter availability start date and time (YYYY MM DD HH MM): ";
            doctors[i].begin.year = getValidInteger();
            doctors[i].begin.month = getValidInteger();
            doctors[i].begin.day = getValidInteger();
            doctors[i].begin.time.hour = getValidInteger();
            doctors[i].begin.time.min = getValidInteger();

            cout << "Enter availability end date and time (YYYY MM DD HH MM): ";
            doctors[i].end.year = getValidInteger();
            doctors[i].end.month = getValidInteger();
            doctors[i].end.day = getValidInteger();
            doctors[i].end.time.hour = getValidInteger();
            doctors[i].end.time.min = getValidInteger();

            cout << "Doctor availability updated successfully.\n";
            return;
        }
    }
    cout << "Doctor not found!\n";
}

void doctorMenu(int doctorId)
{
    int choice;

    do
    {
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. View Appointments\n";
        cout << "2. Set Availability\n";
        cout << "3. Set Fee\n";
        cout << "4. Logout\n";
        choice = getValidInteger();
        if (choice == 1)
        {
            viewDoctorSchedule(doctorId);
        }
        else if (choice == 2)
        {
            setDoctorAvailability(doctorId);
        }
        else if (choice == 3)
        {
            setDoctorFee(doctorId);
        }
        else if (choice == 4)
        {
            cout << "Logging out. Goodbye!\n";
            return;
        }
        else
            cout << "Invalid choice! Please try again.\n";
    } while (choice != 4);
}

int Doctorlogin()
{
    int id;
    string password;

    cout << "\n--- Doctor Login ---\n";
    cout << "Enter your doctor ID: ";
    id = getValidInteger();

    if (id < 0)
    {
        cout << "\nInvalid ID!\n";
        return -1;
    }

    cout << "Enter your password: ";
    cin.ignore();
    getline(cin, password);

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == id &&
            doctors[i].password == password)
        {
            cout << "\nWelcome " << doctors[i].name << endl;
            return doctors[i].doctorId;
        }
    }

    cout << "\nInvalid ID or password!\n";
    return -1;
}

void doctorMainMenu()
{
    int choice;

    do
    {
        cout << "\n--- Doctor Menu ---\n";
        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidInteger();

        if (choice == 1)
        {
            int id = Doctorlogin();
            if (id != -1)
                doctorMenu(id);
        }
        else if (choice == 2)
        {
            cout << "Exiting the program. Goodbye!\n";
        }
        else
            cout << "Invalid choice! Please try again.\n";

    } while (choice != 2);
}

bool isPhoneUsed(string phone)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].phoneNumber == phone)
        {
            return true;
        }
    }
    return false;
}

void viewAppointments(int patientId)
{
    cout << "\n--- Your Appointments ---\n";
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].patientId == patientId)
        {
            cout << "Appointment ID: " << appointments[i].appointmentId << endl;
            cout << "Doctor ID: " << appointments[i].doctorId << endl;
            cout << "Date: " << appointments[i].appointmentDate.year << "-"
                 << appointments[i].appointmentDate.month << "-"
                 << appointments[i].appointmentDate.day << endl;
            cout << "Time: " << appointments[i].appointmentTime.hour << ":"
                 << appointments[i].appointmentTime.min << endl;
            cout << "Status: " << appointments[i].status << endl;
            cout << "Total Cost: $" << appointments[i].totalCost << endl;
            cout << "-----------------------------\n";
        }
    }
}

bool IsDigit(string phone)
{
    if (phone.empty())
        return false;
    for (size_t i = 0; i < phone.length(); i++)
    {
        if (!isdigit(phone[i]))
        {
            return false;
        }
    }
    return true;
}

void signUp()
{
    if (patientCount >= max_patient)
    {
        cout << "Patient list is full!" << endl;
        return;
    }

    patient newPatient;
    newPatient.patientId = patientCount + 1;
    cout << "\n--- Sign Up ---\n";

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, newPatient.name);

    cout << "Enter your password: ";
    getline(cin, newPatient.password);
    bool usage;

    do
    {
        cout << "Enter your phone number: ";
        getline(cin, newPatient.phoneNumber);
        usage = isPhoneUsed(newPatient.phoneNumber);
        if (!IsDigit(newPatient.phoneNumber))
        {
            cout << "Phone number must contain only digits! Try again.\n";
        }
        if (usage)
        {
            cout << "Phone already used! Try again.\n";
        }

    } while (usage || !IsDigit(newPatient.phoneNumber));

    cout << "Enter your age: ";
    newPatient.age = getValidInteger();

    patients[patientCount] = newPatient;
    patientCount++;

    cout << "\nSign Up successful! Your Patient ID is "
         << newPatient.patientId << endl;
}

int zellersCongruence(int day, int month, int year)
{
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;

    int dayIndex = (h + 6) % 7;
    return dayIndex;
}

int login()
{
    int id;
    string password;

    cout << "\n--- Login ---\n";
    cout << "Enter your Patient ID: ";
    id = getValidInteger();

    cout << "Enter your password: ";
    cin.ignore();
    getline(cin, password);

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patientId == id &&
            patients[i].password == password)
        {
            cout << "\nWelcome " << patients[i].name << endl;
            return patients[i].patientId;
        }
    }

    cout << "\nInvalid ID or password!\n";
    return -1;
}

string isAvailable(int doctorId, date appointmentDate, duration appointmentTime)
{
    int doctorIndex = -1;
    for (int i = 0; i < doctorCount; i++)
    {
        if (doctors[i].doctorId == doctorId)
        {
            doctorIndex = i;
            break;
        }
    }
    if (doctorIndex == -1)
        return "Doctor not found.";

    doctor &doc = doctors[doctorIndex];

    bool dayOk = false;
    for (int i = 0; i < daysize; i++)
    {
        if (appointmentDate.specificDay == doc.AvalableSlots[i])
        {
            dayOk = true;
            break;
        }
    }
    if (!dayOk)
        return "this day is not available please choose another day";

    if (appointmentTime.hour < 0 || appointmentTime.hour > 23 ||
        appointmentTime.min < 0 || appointmentTime.min > 59)
    {
        return "You are out of bounds.";
    }

    if ((appointmentTime.hour < doc.begin.time.hour) ||
        (appointmentTime.hour == doc.begin.time.hour && appointmentTime.min < doc.begin.time.min) ||
        (appointmentTime.hour > doc.end.time.hour) ||
        (appointmentTime.hour == doc.end.time.hour && appointmentTime.min > doc.end.time.min))
    {
        return "You are out of bounds.";
    }

    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].doctorId == doctorId &&
            appointments[i].appointmentDate.year == appointmentDate.year &&
            appointments[i].appointmentDate.month == appointmentDate.month &&
            appointments[i].appointmentDate.day == appointmentDate.day &&
            appointments[i].appointmentTime.hour == appointmentTime.hour &&
            appointments[i].appointmentTime.min == appointmentTime.min &&
            appointments[i].status != "Cancelled")
        {
            return "Doctor is not available.";
        }
    }

    return "Doctor is available.";
}

void bookAppointment(int id)
{
    if (appointmentCount >= max_appointment)
    {
        cout << "Appointment list is full!" << endl;
        return;
    }
    int doctorIndex = 0;
    appointment newAppointment;
    newAppointment.appointmentId = appointmentCount + 1;
    string availability;

    do
    {
        cout << "\n--- Book Appointment ---\n";

        newAppointment.patientId = id;
        cout << "Enter Doctor ID: ";
        newAppointment.doctorId = getValidInteger();

        if (newAppointment.doctorId < 0)
        {
            cout << "Invalid doctor ID! Please try again.\n";
            continue;
        }
        bool doctorFound = false;
        for (int i = 0; i < doctorCount; i++)
        {
            if (doctors[i].doctorId == newAppointment.doctorId)
            {
                cout << "Doctor Name: " << doctors[i].name << endl;
                cout << "Consultation Fee: $" << doctors[i].consultationFee << endl;
                doctorFound = true;
                doctorIndex = i;
                break;
            }
        }
        if (!doctorFound)
        {
            int choice00;
            cout << "Doctor not found! \n 1.Try again.\n"
                 << "2. main menu.\n";
            choice00 = getValidInteger();
            if (choice00 == 1)
                continue;
            else
                return;
        }

        cout << "Enter Appointment Date (YYYY MM DD): ";
        newAppointment.appointmentDate.year = getValidInteger();
        newAppointment.appointmentDate.month = getValidInteger();
        newAppointment.appointmentDate.day = getValidInteger();

        newAppointment.appointmentDate.specificDay = zellersCongruence(newAppointment.appointmentDate.day, newAppointment.appointmentDate.month, newAppointment.appointmentDate.year);

        cout << "Enter Appointment Time (HH MM): ";
        newAppointment.appointmentTime.hour = getValidInteger();
        newAppointment.appointmentTime.min = getValidInteger();

        availability = isAvailable(newAppointment.doctorId, newAppointment.appointmentDate, newAppointment.appointmentTime);

        if (availability == "Doctor is available.")
            newAppointment.status = "Booked";
        else if (availability == "Doctor is not available.")
            cout << "Not Booked: Slot is unavailable, Try again!\n";
        else if (availability == "You are out of bounds.")
            cout << "Out of doctor's working hours, Try again!\n";
        else if (availability == "this day is not available please choose another day")
            cout << "Doctor does not work on this day, Try again!\n";

    } while (availability != "Doctor is available.");

    newAppointment.totalCost = doctors[doctorIndex].consultationFee;
    appointments[appointmentCount] = newAppointment;
    appointmentCount++;

    cout << "\nAppointment booked successfully! Your Appointment ID is "
         << newAppointment.appointmentId << endl;
}

bool cancelAppointment(int appointmentId, int patientId)
{
    for (int i = 0; i < appointmentCount; i++)
    {
        if (appointments[i].appointmentId == appointmentId)
        {
            if (appointments[i].patientId != patientId)
            {
                cout << "You don't have permission to cancel this appointment.\n";
                return false;
            }
            if (appointments[i].status == "Cancelled")
            {
                cout << "This appointment is already cancelled.\n";
                return false;
            }
            if (appointments[i].status == "Completed")
            {
                cout << "Cannot cancel a completed appointment.\n";
                return false;
            }

            appointments[i].status = "Cancelled";
            return true;
        }
    }
    cout << "Appointment not found.\n";
    return false;
}

void viewDoctors()
{
    for (int i = 0; i < doctorCount; i++)
    {
        cout << "Doctor Number " << i + 1 << "\n"
             << "Doctor's Id : " << doctors[i].doctorId
             << "\nDoctor's Name : " << doctors[i].name
             << "\nDoctor's Working Days : ";
        printWorkDays(doctors[i].AvalableSlots);
        cout << "Doctor's working hours : " << doctors[i].begin.time.hour << ":" << doctors[i].begin.time.min << " to " << doctors[i].end.time.hour << ":" << doctors[i].end.time.min << endl;
        cout << "Doctor's specialization : " << doctors[i].specialization
             << "\nDoctor's consultation Fee : $" << doctors[i].consultationFee << endl;
        cout << "-----------------------------\n";
    }
}

void internalMenu(int id)
{
    patient currentPatient;
    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].patientId == id)
        {
            currentPatient = patients[i];
            break;
        }
    }
    int choice = 0;
    do
    {
        cout << "\n--- Welcome " << currentPatient.name << " to the Hospital Management System ---\n"
             << "1. Book an Appointment\n"
             << "2. View Appointments\n"
             << "3. Cancel an Appointment\n"
             << "4. View Doctors\n"
             << "5. Logout\n";
        choice = getValidInteger();
        if (choice == 1)
            bookAppointment(id);
        else if (choice == 2)
            viewAppointments(id);
        else if (choice == 3)
        {
            int appointmentId;
            cout << "Enter the Appointment ID to cancel: \n";
            appointmentId = getValidInteger();
            bool cancel = cancelAppointment(appointmentId, id);
            if (cancel)
                cout << "Appointment cancelled successfully.\n";
        }
        else if (choice == 4)
        {
            viewDoctors();
        }
        else if (choice == 5)
        {
            cout << "Logging out. Goodbye!\n";
            return;
        }
        else
            cout << "Invalid choice! Please try again.\n";

    } while (choice != 5);
}

void patientMenu()
{
    int choice;

    do
    {
        cout << "\n--- Patient Menu ---\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        choice = getValidInteger();
        if (choice == 1)
        {
            signUp();
        }
        else if (choice == 2)
        {
            int id = login();
            if (id != -1)
                internalMenu(id);
        }
        else if (choice == 3)
        {
            cout << "Exiting the program. Goodbye!\n";
        }
        else
            cout << "Invalid choice! Please try again.\n";

    } while (choice != 3);
}

void initial()
{
    admins[0] = {1, "Admin", "Admin"};
    adminCount = 1;

    patients[0] = {1, "Ali Mohamed", "ali123", "01012345678", 28};
    patients[1] = {2, "Nour Tarek", "nour123", "01098765432", 22};
    patientCount = 2;

    doctors[0] = {1, "Dr. Ahmed Khalil", {0, 1, 2, 3, 4, -1, -1}, "Cardiology", {2025, 1, 1, 0, {9, 0}}, {2025, 12, 31, 0, {17, 0}}, 200.0, "ahmed123"};
    doctors[1] = {2, "Dr. Sara Mostafa", {0, 1, 2, 3, 4, -1, -1}, "Dermatology", {2025, 1, 1, 0, {9, 0}}, {2025, 12, 31, 0, {17, 0}}, 150.0, "sara123"};
    doctors[2] = {3, "Dr. Omar Hassan", {0, 1, -1, 3, 4, -1, -1}, "Orthopedics", {2025, 1, 1, 0, {9, 0}}, {2025, 12, 31, 0, {17, 0}}, 250.0, "omar123"};
    doctorCount = 3;
    nextDoctorId = 4;
}

void saveData()
{
    ofstream f("doctors.txt");
    f << doctorCount << "\n";
    f << nextDoctorId << "\n";    // ← save nextDoctorId
    for (int i = 0; i < doctorCount; i++)
    {
        f << doctors[i].doctorId << "\n";
        f << doctors[i].name << "\n";
        for (int j = 0; j < daysize; j++)
            f << doctors[i].AvalableSlots[j] << " ";
        f << "\n";
        f << doctors[i].specialization << "\n";
        f << doctors[i].consultationFee << "\n";
        f << doctors[i].password << "\n";
        f << doctors[i].begin.year << " " << doctors[i].begin.month << " "
          << doctors[i].begin.day << " " << doctors[i].begin.time.hour << " "
          << doctors[i].begin.time.min << "\n";
        f << doctors[i].end.year << " " << doctors[i].end.month << " "
          << doctors[i].end.day << " " << doctors[i].end.time.hour << " "
          << doctors[i].end.time.min << "\n";
    }
    f.close();

    ofstream f2("patients.txt");
    f2 << patientCount << "\n";
    for (int i = 0; i < patientCount; i++)
    {
        f2 << patients[i].patientId << "\n";
        f2 << patients[i].name << "\n";
        f2 << patients[i].password << "\n";
        f2 << patients[i].phoneNumber << "\n";
        f2 << patients[i].age << "\n";
    }
    f2.close();

    ofstream f3("appointments.txt");
    f3 << appointmentCount << "\n";
    for (int i = 0; i < appointmentCount; i++)
    {
        f3 << appointments[i].appointmentId << "\n";
        f3 << appointments[i].doctorId << "\n";
        f3 << appointments[i].patientId << "\n";
        f3 << appointments[i].appointmentDate.year << " "
           << appointments[i].appointmentDate.month << " "
           << appointments[i].appointmentDate.day << " "
           << appointments[i].appointmentDate.specificDay << "\n";
        f3 << appointments[i].appointmentTime.hour << " "
           << appointments[i].appointmentTime.min << "\n";
        f3 << appointments[i].status << "\n";
        f3 << appointments[i].totalCost << "\n";
    }
    f3.close();
}

void loadData()
{
    ifstream f("doctors.txt");
    if (f.is_open())
    {
        f >> doctorCount;
        f >> nextDoctorId;        // ← load nextDoctorId
        f.ignore();
        for (int i = 0; i < doctorCount; i++)
        {
            f >> doctors[i].doctorId;
            f.ignore();
            getline(f, doctors[i].name);
            for (int j = 0; j < daysize; j++)
                f >> doctors[i].AvalableSlots[j];
            f.ignore();
            getline(f, doctors[i].specialization);
            f >> doctors[i].consultationFee;
            f.ignore();
            getline(f, doctors[i].password);
            f >> doctors[i].begin.year >> doctors[i].begin.month >> doctors[i].begin.day >> doctors[i].begin.time.hour >> doctors[i].begin.time.min;
            f >> doctors[i].end.year >> doctors[i].end.month >> doctors[i].end.day >> doctors[i].end.time.hour >> doctors[i].end.time.min;
            f.ignore();
        }
        f.close();
    }

    ifstream f2("patients.txt");
    if (f2.is_open())
    {
        f2 >> patientCount;
        f2.ignore();
        for (int i = 0; i < patientCount; i++)
        {
            f2 >> patients[i].patientId;
            f2.ignore();
            getline(f2, patients[i].name);
            getline(f2, patients[i].password);
            getline(f2, patients[i].phoneNumber);
            f2 >> patients[i].age;
            f2.ignore();
        }
        f2.close();
    }

    ifstream f3("appointments.txt");
    if (f3.is_open())
    {
        f3 >> appointmentCount;
        f3.ignore();
        for (int i = 0; i < appointmentCount; i++)
        {
            f3 >> appointments[i].appointmentId;
            f3 >> appointments[i].doctorId;
            f3 >> appointments[i].patientId;
            f3 >> appointments[i].appointmentDate.year >> appointments[i].appointmentDate.month >> appointments[i].appointmentDate.day >> appointments[i].appointmentDate.specificDay;
            f3 >> appointments[i].appointmentTime.hour >> appointments[i].appointmentTime.min;
            f3.ignore();
            getline(f3, appointments[i].status);
            f3 >> appointments[i].totalCost;
            f3.ignore();
        }
        f3.close();
    }
}
