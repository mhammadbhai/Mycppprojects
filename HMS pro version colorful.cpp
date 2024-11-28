#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm> // Include the algorithm library for sorting
#include <limits>
#include <chrono>
#include <thread>

using namespace std;

// Define constants for array sizes
const int MAX_PATIENTS = 100;
const int MAX_DOCTORS = 10;
const int MAX_DIAGNOSES = 10;
const int MAX_APPOINTMENTS = 5;

// ANSI escape codes for coloring
const string RESET = "\033[0m";
const string BOLD = "\033[1m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

// Define Patient and Doctor classes
class Doctor {
public:
    string name;
    string specialization;
    string availableTimes[MAX_APPOINTMENTS];

    Doctor() {}
    Doctor(string n, string s, const string t[MAX_APPOINTMENTS]) : name(n), specialization(s) {
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            availableTimes[i] = t[i];
        }
    }

    string get_doctor_name() const {
        return name;
    }

    string get_doctor_specialization() const {
        return specialization;
    }

    string* get_available_times() {
        return availableTimes;
    }
};

class Patient {
	private:
		string doctorSpecialization;
		
public:
	friend class Doctor;
    string name;
    int age;
    string diagnosis;
    string doctorName;
    string appointmentTime;
    string appointmentDate;

    Patient() {}

    void setpatientdata(string pname, int page, string pdiagnosis, string dname, string atime,string adate) {
        name = pname;
        age = page;
        diagnosis = pdiagnosis;
        doctorName = dname;
        appointmentTime = atime;
        appointmentDate = adate;
    }

    string get_patient_name() const {
        return name;
    }

    int get_patient_age() const {
        return age;
    }

    string get_patient_diagnosis() const {
        return diagnosis;
    }

    string get_doctor_name() const {
        return doctorName;
    }

    string get_appointment_time() const {
        return appointmentTime;
    }
    string get_appointment_date() const {
        return appointmentDate; 
    }
};

// Initialize global variables
string diagnoses[MAX_DIAGNOSES] = {"Hypertension", "Diabetes", "Heart Disease", "Cancer", "Chronic Lower Respiratory Disease", "Stroke", "Alzheimer's Disease", "Arthritis", "Depression", "Obesity"};

string cardiologistTimes[MAX_APPOINTMENTS] = {"9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM"};
string endocrinologistTimes[MAX_APPOINTMENTS] = {"1:00 PM", "2:00 PM", "3:00 PM", "4:00 PM", "5:00 PM"};
string cardiothoracicSurgeonTimes[MAX_APPOINTMENTS] = {"2:00 PM", "3:00 PM", "4:00 PM", "5:00 PM", "6:00 PM"};
string oncologistTimes[MAX_APPOINTMENTS] = {"10:00 AM", "11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM"};
string pulmonologistTimes[MAX_APPOINTMENTS] = {"3:00 PM", "4:00 PM", "5:00 PM", "6:00 PM", "7:00 PM"};
string neurologistTimes[MAX_APPOINTMENTS] = {"11:00 AM", "12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM"};
string geriatricianTimes[MAX_APPOINTMENTS] = {"8:00 AM", "9:00 AM", "10:00 AM", "11:00 AM", "12:00 PM"};
string rheumatologistTimes[MAX_APPOINTMENTS] = {"12:00 PM", "1:00 PM", "2:00 PM", "3:00 PM", "4:00 PM"};
string psychiatristTimes[MAX_APPOINTMENTS] = {"4:00 PM", "5:00 PM", "6:00 PM", "7:00 PM", "8:00 PM"};
string generalSurgeonTimes[MAX_APPOINTMENTS] = {"7:00 AM", "8:00 AM", "9:00 AM", "10:00 AM", "11:00 AM"};

Doctor doctors[MAX_DOCTORS] = {
    Doctor("Dr. Smith", "Cardiologist", cardiologistTimes),
    Doctor("Dr. Brown", "Endocrinologist", endocrinologistTimes),
    Doctor("Dr. Jones", "Cardiothoracic Surgeon", cardiothoracicSurgeonTimes),
    Doctor("Dr. Garcia", "Oncologist", oncologistTimes),
    Doctor("Dr. Martinez", "Pulmonologist", pulmonologistTimes),
    Doctor("Dr. Robinson", "Neurologist", neurologistTimes),
    Doctor("Dr. Clark", "Geriatrician", geriatricianTimes),
    Doctor("Dr. Rodriguez", "Rheumatologist", rheumatologistTimes),
    Doctor("Dr. Lewis", "Psychiatrist", psychiatristTimes),
    Doctor("Dr. Lee", "General Surgeon", generalSurgeonTimes)
};

Patient patients[MAX_PATIENTS];
int numofpatients = 0;
void showWelcomeScreen() {
    system("cls"); // Clear screen (Windows specific)
    cout << RED << "*********************************************" << RESET << endl;
    cout << GREEN << "*                                           *" << RESET << endl;
    cout << YELLOW << "*    " << BLUE << "Welcome to the Healthcare Management" << YELLOW << "   *" << RESET << endl;
    cout << CYAN << "*                 " << MAGENTA << "System" << CYAN << "                    *" << RESET << endl;
    cout << GREEN << "*                                           *" << RESET << endl;
    cout << RED << "*********************************************" << RESET << endl;
    this_thread::sleep_for(chrono::seconds(2)); // Pause for 2 seconds to display the welcome screen
}
void showMainMenu() {
    system("cls"); // Clear screen (Windows specific)

    cout << RED << "*********************************************" << RESET << endl;
    cout << GREEN << "*\t\t    " << YELLOW << "MENU" << GREEN << "\t\t    *" << RESET << endl;
    cout << RED << "*********************************************" << RESET << endl;
    cout << CYAN << "Enter choice." << RESET << endl;
    cout << BLUE << "\t1. " << MAGENTA << "Input Data" << RESET << endl;
    cout << BLUE << "\t2. " << MAGENTA << "Show Patient Data" << RESET << endl;
    cout << BLUE << "\t3. " << MAGENTA << "Show Appointments" << RESET << endl;
    cout << BLUE << "\t4. " << MAGENTA << "Manage Data" << RESET << endl;
    cout << BLUE << "\t6. " << RED << "EXIT" << RESET << endl;
}
bool isValidDate(const string& date) {
    int day, month, year;
    istringstream iss(date);
    char ch;

    if (!(iss >> day) || !(iss >> ch) || !(iss >> month) || !(iss >> ch) || !(iss >> year)) {
        return false;
    }

    if (month < 1 || month > 12) {
        return false;
    }

    if (day < 1 || day > 31) {
        return false;
    }

    if (month == 2) {
        if (year % 4 != 0) {
            if (day > 28) {
                return false;
            }
        } else {
            if (day > 29) {
                return false;
            }
        }
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    return true;
}
void inputPatientData() {
    while (true) {
        system("cls");
        cout << RED << "*********************************************" << RESET << endl;
        cout << GREEN << "\t\tPATIENT DETAILS" << RESET << endl;
        cout << RED << "*********************************************" << RESET << endl;

        string pname;
        int page;
        string pdiagnosis;
        string dname;
        string atime;
        string adate;
        int s_disease;
        int s_doctor;
        int s_time;
        string choice1;
        cout << CYAN << "Enter the Patient Name: " << RESET;
        cin.ignore();
        getline(cin, pname);

        // Validate and ensure that age input is an integer
        while (true) {
            cout << CYAN << "Enter Patient Age: " << RESET;
            if (cin >> page) {
                break; // If input is an integer, break out of the loop
            } else {
                cout << RED << "Invalid input. Age must be an integer. Please try again." << RESET << endl;
                cin.clear(); // Clear error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }

        // Listing and Selection of Disease
        bool validDiseaseSelected = false; // Flag to track valid disease selection
        while (!validDiseaseSelected) {
            cout << "\n" << YELLOW << "Available Diseases:" << RESET << "\n";
            for (int i = 0; i < MAX_DIAGNOSES; ++i) {
                cout << BLUE << i + 1 << ". " << MAGENTA << diagnoses[i] << RESET << endl;
            }
            cout << CYAN << "Select Disease: " << RESET;
            cin >> s_disease;
            if (s_disease >= 1 && s_disease <= MAX_DIAGNOSES) {
                validDiseaseSelected = true; // Mark the selection as valid
            } else {
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
            }
        }
        pdiagnosis = diagnoses[s_disease - 1]; // Corrected index

        // Listing and Selection of Doctor according to disease
        cout << "\n" << YELLOW << "Available Doctors:" << RESET << "\n";
        int validDoctorIndices[MAX_DOCTORS]; // Array to store valid doctor indices
        int validDoctorCount = 0; // Counter for the number of valid doctors
        for (int i = 0; i < MAX_DOCTORS; ++i) {
            if ((pdiagnosis == "Hypertension" && doctors[i].get_doctor_specialization() == "Cardiologist") ||
                (pdiagnosis == "Diabetes" && doctors[i].get_doctor_specialization() == "Endocrinologist") ||
                (pdiagnosis == "Heart Disease" && doctors[i].get_doctor_specialization() == "Cardiothoracic Surgeon") ||
                (pdiagnosis == "Cancer" && doctors[i].get_doctor_specialization() == "Oncologist") ||
                (pdiagnosis == "Chronic Lower Respiratory Disease" && doctors[i].get_doctor_specialization() == "Pulmonologist") ||
                (pdiagnosis == "Stroke" && doctors[i].get_doctor_specialization() == "Neurologist") ||
                (pdiagnosis == "Alzheimer's Disease" && doctors[i].get_doctor_specialization() == "Geriatrician") ||
                (pdiagnosis == "Arthritis" && doctors[i].get_doctor_specialization() == "Rheumatologist") ||
                (pdiagnosis == "Depression" && doctors[i].get_doctor_specialization() == "Psychiatrist") ||
                (pdiagnosis == "Obesity" && doctors[i].get_doctor_specialization() == "General Surgeon")) {
                cout << BLUE << validDoctorCount + 1 << ". " << MAGENTA << doctors[i].get_doctor_name() << " - " << doctors[i].get_doctor_specialization() << RESET << endl;
                validDoctorIndices[validDoctorCount] = i; // Store the index of the valid doctor
                validDoctorCount++;
            }
        }

        // Validate doctor selection
        bool validDoctorSelected = false;
        while (!validDoctorSelected) {
            cout << CYAN << "Select Doctor: " << RESET;
            cin >> s_doctor;
            if (s_doctor >= 1 && s_doctor <= validDoctorCount) {
                validDoctorSelected = true; // Mark the selection as valid
            } else {
                cout << RED << "Invalid choice. Please select a doctor from the displayed list." << RESET << endl;
            }
        }
        s_doctor = validDoctorIndices[s_doctor - 1]; // Adjust index to match the original array
        dname = doctors[s_doctor].get_doctor_name();

        // Listing and Selection of Appointment Time
        cout << "\n" << YELLOW << "Available Appointment Times:" << RESET << "\n";
        string* times = doctors[s_doctor].get_available_times();
        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
            cout << BLUE << i + 1 << ". " << MAGENTA << times[i] << RESET << endl;
        }
        bool validAppointmentTime = false;
        while (!validAppointmentTime) {
            cout << CYAN << "Select Appointment Time: " << RESET;
            cin >> s_time;
            s_time--; // Adjust index to match the array index
            atime = times[s_time];

            // Check if the selected appointment time is available
            bool isTimeAvailable = true;
            for (int i = 0; i < numofpatients; ++i) {
                if (patients[i].get_doctor_name() == dname && patients[i].get_appointment_time() == atime) {
                    isTimeAvailable = false;
                    break;
                }
            }

            if (isTimeAvailable) {
                validAppointmentTime = true;
            } else {
                cout << RED << "Appointment time is already taken. Please select another time." << RESET << endl;
            }
        }

        while (true) {
            cout << CYAN << "Enter Appointment Date (DD-MM-YYYY): " << RESET;
            cin.ignore();
            getline(cin, adate);
            if (isValidDate(adate)) {
                break; // If the date is valid, exit the loop
            } else {
                cout << RED << "Invalid date format. Please enter the date in (DD-MM-YYYY) format." << RESET << endl;
            }
        }

        // Display patient details and confirm appointment
        system("cls");
        cout << YELLOW << "Confirm Patient Appointment:" << RESET << endl;
        cout << "Patient Name: " << pname << endl;
        cout << "Patient Age: " << page << endl;
        cout << "Diagnosis: " << pdiagnosis << endl;
        cout << "Doctor: " << dname << endl;
        cout << "Appointment Time: " << atime << endl;
        cout << "Appointment Date: " << adate << endl;

        cout << YELLOW << "Confirm Appointment? (Y/N): " << RESET;
        cin >> choice1;
        if (choice1 == "Y" || choice1 == "y") {
            // Set the patient data
            patients[numofpatients].setpatientdata(pname, page, pdiagnosis, dname, atime, adate);
            numofpatients++;
            cout << GREEN << "Appointment Confirmed. Data Entered Successfully!" << RESET << endl;
        } else {
            cout << YELLOW << "Appointment Canceled. Data Not Saved." << RESET << endl;
        }
		cout << "\n" << YELLOW << "Would you like to enter data for another patient? (Y/N): " << RESET;
        cin >> choice1;
        if (choice1 != "Y" && choice1 != "y") {
            break;
        }
    }
}
void manageData() {
    if (numofpatients == 0) {
        cout << RED << "No patient data available." << RESET << endl;system("pause");
    } else {
        while (true) {
            system("cls");
            cout << GREEN << "*********************************************" << RESET << endl;
            cout << CYAN << "\t\tMANAGE DATA" << RESET << endl;
            cout << GREEN << "*********************************************" << RESET << endl;

            int choice;
            cout << YELLOW << "\t1. Delete Patient Data" << endl;
            cout << "\t2. Cancel Appointment" << endl;
            cout << "\t3. Change Appointment Timing" << endl;
            cout << "\t4. Return to Main Menu" << endl;
            cout << "Enter your choice: " << RESET;
            cin >> choice;

            switch (choice) {
                case 1: {
                    string patientName;
                    cout << YELLOW << "Enter the name of the patient to delete: " << RESET;
                    cin.ignore();
                    getline(cin, patientName);

                    // Search for the patient by name and delete if found
                    bool found = false;
                    for (int i = 0; i < numofpatients; ++i) {
                        if (patients[i].get_patient_name() == patientName) {
                            // Shift elements to the left to fill the gap
                            for (int j = i; j < numofpatients - 1; ++j) {
                                patients[j] = patients[j + 1];
                            }
                            numofpatients--; // Decrement the number of patients
                            found = true;
                            break;
                        }
                    }
                    if (found) {
                        cout << GREEN << "Patient data deleted successfully." << RESET << endl;
                    } else {
                        cout << RED << "Patient not found." << RESET << endl;
                    }
                    break;
                }
                case 2: {
                    string patientName;
                    cout << YELLOW << "Enter the name of the patient to cancel the appointment: " << RESET;
                    cin.ignore();
                    getline(cin, patientName);

                    // Search for the patient by name and cancel appointment if found
                    bool found = false;
                    for (int i = 0; i < numofpatients; ++i) {
                        if (patients[i].get_patient_name() == patientName) {
                            // Clear appointment details
                            patients[i].appointmentTime = "";
                            patients[i].appointmentDate = "";
                            found = true;
                            break;
                        }
                    }

                    if (found) {
                        cout << GREEN << "Appointment canceled successfully." << RESET << endl;
                    } else {
                        cout << RED << "Patient not found." << RESET << endl;
                    }
                    break;
                }
                case 3: {
                    string patientName;
                    cout << YELLOW << "Enter the name of the patient to change the appointment timing: " << RESET;
                    cin.ignore();
                    getline(cin, patientName);

                    // Search for the patient by name
                    int patientIndex = -1;
                    for (int i = 0; i < numofpatients; ++i) {
                        if (patients[i].get_patient_name() == patientName) {
                            patientIndex = i;
                            break;
                        }
                    }

                    if (patientIndex != -1) {
                        // Display the patient's current appointment details
                        cout << GREEN << "Current Appointment Details:" << RESET << endl;
                        cout << "Patient Name: " << patients[patientIndex].get_patient_name() << endl;
                        cout << "Doctor: " << patients[patientIndex].get_doctor_name() << endl;
                        cout << "Appointment Time: " << patients[patientIndex].get_appointment_time() << endl;
                        cout << "Appointment Date: " << patients[patientIndex].get_appointment_date() << endl;

                        // Display available appointment times for the patient's doctor
                        string* times = doctors[patientIndex].get_available_times();
                        cout << YELLOW << "\nAvailable Appointment Times:" << RESET << endl;
                        for (int i = 0; i < MAX_APPOINTMENTS; ++i) {
                            cout << i + 1 << ". " << times[i] << endl;
                        }

                        int newTimeIndex;
                        cout << YELLOW << "Select the new appointment time: " << RESET;
                        cin >> newTimeIndex;
                        newTimeIndex--; // Adjust index to match array index

                        if (newTimeIndex >= 0 && newTimeIndex < MAX_APPOINTMENTS) {
                            // Change appointment time
                            patients[patientIndex].appointmentTime = times[newTimeIndex];
                            cout << GREEN << "Appointment time updated successfully." << RESET << endl;

                            // Update the appointment date input
                            string newAppointmentDate;
                            while (true) {
    							cout << CYAN << "Enter Appointment Date (DD-MM-YYYY): " << RESET;
							    string newAppointmentDate;
							    cin >> newAppointmentDate;
							    if (isValidDate(newAppointmentDate)) {
						        	patients[patientIndex].appointmentDate = newAppointmentDate;
        							break; // If the date is valid, exit the loop
    							} else {
        							cout << RED << "Invalid date format. Please enter the date in (DD-MM-YYYY) format." << RESET << endl;
        							cin.clear(); // Clear error flags
        							cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
    							}
							}
                        } else {
                            cout << RED << "Invalid appointment time." << RESET << endl;
                        }
                    } else {
                        cout << RED << "Patient not found." << RESET << endl;
                    }
                    break;
                }
                case 4:
                    return; // Return to main menu
                default:
                    cout << RED << "Invalid choice. Please try again." << RESET << endl;
                    system("pause");
            }

            // Pause the program before continuing
            cout << YELLOW << "Press Enter to continue..." << RESET;
            cin.ignore();
            cin.get();
        }
    }
}


void showPatientData() {
    system("cls");
    cout << RED << "*********************************************" << RESET << endl;
    cout << GREEN << "\t\tPATIENT DATA" << RESET << endl;
    cout << RED << "*********************************************" << RESET << endl;

    if (numofpatients == 0) {
        cout << RED << "No patient data available." << RESET << endl;
        system("pause");
    } else {
        while (true) {
            start:
            system("cls");
            cout << RED << "*********************************************" << RESET << endl;
            cout << GREEN << "\t\tPATIENT DATA" << RESET << endl;
            cout << RED << "*********************************************" << RESET << endl;

            int choice;
            cout << YELLOW << "Select an option to view patient data:" << RESET << endl;
            cout << CYAN << "1. Show all patient data" << RESET << endl;
            cout << CYAN << "2. Show patient data by name" << RESET << endl;
            cout << CYAN << "3. Show patient data by age" << RESET << endl;
            cout << CYAN << "4. Return to Main Menu" << RESET << endl;
            cout << YELLOW << "Enter your choice: " << RESET;
            cin >> choice;

            switch (choice) {
                case 1:
                    // Show all patient data in tabular format
                    system("cls");
                    cout << RED << "******************************************************************************************************************************" << RESET << endl;
                    cout << GREEN << "\t\t\tPATIENT DETAIL" << RESET << endl;
                    cout << RED << "******************************************************************************************************************************" << RESET << endl;
                    cout << YELLOW << "\tSort By: None" << RESET << endl;
                    cout << RED << "******************************************************************************************************************************" << RESET << endl;
                    cout << WHITE << setw(20) << left << "Patient Name" << setw(10) << left << "Age" << setw(15) << left << "Diagnosis" << setw(20) << left << "Doctor" << setw(25) << left << "Doctor Specialization" << setw(20) << left << "Appointment Time" << setw(20) << left << "Appointment Date" << RESET << endl;
                    cout << RED << "******************************************************************************************************************************" << RESET << endl;
                    for (int i = 0; i < numofpatients; ++i) {
                        cout << CYAN << setw(20) << left << patients[i].get_patient_name()
                             << setw(10) << left << patients[i].get_patient_age()
                             << setw(15) << left << patients[i].get_patient_diagnosis()
                             << setw(20) << left << patients[i].get_doctor_name()
                             << setw(25) << left << doctors[i].get_doctor_specialization()
                             << setw(20) << left << patients[i].get_appointment_time()
                             << setw(20) << left << patients[i].get_appointment_date() << RESET << endl;
                    }
                    cout << endl;
                    system("pause");
                    break;

                case 2: {
                        // Sort patients by name before displaying
                        sort(patients, patients + numofpatients, [](const Patient& a, const Patient& b) {
                            return a.get_patient_name() < b.get_patient_name();
                        });

                        string s_pname;
                        cout << YELLOW << "Enter patient name: " << RESET;
                        cin.ignore();
                        getline(cin, s_pname);

                        bool found = false;
                        for (int i = 0; i < numofpatients; ++i) {
                            if (patients[i].get_patient_name() == s_pname) {
                                // Display patient data
                                system("cls");
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << GREEN << "\t\t\tPATIENT DETAIL" << RESET << endl;
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << YELLOW << "\tSort By: Name" << RESET << endl;
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << WHITE << setw(20) << left << "Patient Name" << setw(10) << left << "Age" << setw(15) << left << "Diagnosis" << setw(20) << left << "Doctor" << setw(25) << left << "Doctor Specialization" << setw(20) << left << "Appointment Time" << setw(20) << left << "Appointment Date" << RESET << endl;
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << CYAN << setw(20) << left << patients[i].get_patient_name()
                                     << setw(10) << left << patients[i].get_patient_age()
                                     << setw(15) << left << patients[i].get_patient_diagnosis()
                                     << setw(20) << left << patients[i].get_doctor_name()
                                     << setw(25) << left << doctors[i].get_doctor_specialization()
                                     << setw(20) << left << patients[i].get_appointment_time()
                                     << setw(20) << left << patients[i].get_appointment_date() << RESET << endl;
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            cout << RED << "No patient found with the given name." << RESET << endl;
                        }
                        system("pause");
                        break;
                    }

                case 3: {
                        // Sort patients by age before displaying
                        sort(patients, patients + numofpatients, [](const Patient& a, const Patient& b) {
                            return a.get_patient_age() < b.get_patient_age();
                        });

                        // Show patient data by age
                        int age;
                        cout << YELLOW << "Enter patient age: " << RESET;
                        cin >> age;

                        bool found = false;
                        for (int i = 0; i < numofpatients; ++i) {
                            if (patients[i].get_patient_age() == age) {
                                // Display patient data
                                system("cls");
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << GREEN << "\t\t\tPATIENT DETAIL" << RESET << endl;
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << YELLOW << "\tSort By: Age" << RESET << endl;
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << WHITE << setw(20) << left << "Patient Name" << setw(10) << left << "Age" << setw(15) << left << "Diagnosis" << setw(20) << left << "Doctor" << setw(25) << left << "Doctor Specialization" << setw(20) << left << "Appointment Time" << setw(20) << left << "Appointment Date" << RESET << endl;
                                cout << RED << "******************************************************************************************************************************" << RESET << endl;
                                cout << CYAN << setw(20) << left << patients[i].get_patient_name()
                                     << setw(10) << left << patients[i].get_patient_age()
                                     << setw(15) << left << patients[i].get_patient_diagnosis()
                                     << setw(20) << left << patients[i].get_doctor_name()
                                     << setw(25) << left << doctors[i].get_doctor_specialization()
                                     << setw(20) << left << patients[i].get_appointment_time()
                                     << setw(20) << left << patients[i].get_appointment_date() << RESET << endl;
                                found = true;
                            }
                        }

                        if (!found) {
                            cout << RED << "No patient found with the given age." << RESET << endl;
                        }
                        system("pause");
                        break;
                    }

                case 4:
                    return;

                default:
                    cout << RED << "Invalid choice. Please try again." << RESET << endl;
                    system("pause");
                    goto start;
            }
        }
    }
} 

void showAppointments() {
    while (true) {
        system("cls");
        cout << RED << "*********************************************" << RESET << endl;
        cout << GREEN << "\t\tAPPOINTMENTS" << RESET << endl;
        cout << RED << "*********************************************" << RESET << endl;
        cout << YELLOW << "Enter choice to show appointments sorted by:" << RESET << endl;
        cout << CYAN << "\t1. By Doctor Name" << RESET << endl;
        cout << CYAN << "\t2. By Patient Name" << RESET << endl;
        cout << CYAN << "\t3. By Time" << RESET << endl;
        cout << CYAN << "\t4. Return to Main Menu" << RESET << endl;

        int choice;
        cin >> choice;

        if (choice == 4) {
            break;
        }

        if (choice == 1) {
            system("cls");
            cout << RED << "*********************************************" << RESET << endl;
            cout << GREEN << "\t\tDOCTOR LIST" << RESET << endl;
            cout << RED << "*********************************************" << RESET << endl;

            // Display the list of doctors
            for (int i = 0; i < MAX_DOCTORS; ++i) {
                cout << i + 1 << ". " << doctors[i].get_doctor_name() << " (" << doctors[i].get_doctor_specialization() << ")" << endl;
            }

            int selectedDoctorIndex;
            cout << YELLOW << "Select Doctor by number: " << RESET;
            cin >> selectedDoctorIndex;
            if (selectedDoctorIndex < 1 || selectedDoctorIndex > MAX_DOCTORS) {
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
                system("pause");
                continue;
            }

            string selectedDoctorName = doctors[selectedDoctorIndex - 1].get_doctor_name();
            system("cls");
            cout << RED << "*********************************************" << RESET << endl;
            cout << GREEN << "\t\tAPPOINTMENTS FOR " << selectedDoctorName << RESET << endl;
            cout << RED << "*********************************************" << RESET << endl;

            bool hasAppointments = false;
            for (int i = 0; i < numofpatients; ++i) {
                if (patients[i].get_doctor_name() == selectedDoctorName) {
                    cout << CYAN << "Patient Name: " << RESET << patients[i].get_patient_name() << endl;
                    cout << CYAN << "Time: " << RESET << patients[i].get_appointment_time() << endl;
                    cout << CYAN << "Date: " << RESET << patients[i].get_appointment_date() << endl;
                    cout << RED << "------------------------------" << RESET << endl;
                    hasAppointments = true;
                }
            }

            if (!hasAppointments) {
                cout << RED << "No appointments available for this doctor." << RESET << endl;
            }
            system("pause");
            continue;
        }

        if (choice == 3) {
            system("cls");
            cout << RED << "*********************************************" << RESET << endl;
            cout << GREEN << "\t\tAVAILABLE TIMES" << RESET << endl;
            cout << RED << "*********************************************" << RESET << endl;

            // Display the list of unique appointment times
            string uniqueTimes[MAX_APPOINTMENTS * MAX_DOCTORS];
            int uniqueTimesCount = 0;
            for (int i = 0; i < MAX_DOCTORS; ++i) {
                string* times = doctors[i].get_available_times();
                for (int j = 0; j < MAX_APPOINTMENTS; ++j) {
                    bool isUnique = true;
                    for (int k = 0; k < uniqueTimesCount; ++k) {
                        if (uniqueTimes[k] == times[j]) {
                            isUnique = false;
                            break;
                        }
                    }
                    if (isUnique) {
                        uniqueTimes[uniqueTimesCount++] = times[j];
                    }
                }
            }

            sort(uniqueTimes, uniqueTimes + uniqueTimesCount); // Sort the unique times

            for (int i = 0; i < uniqueTimesCount; ++i) {
                cout << i + 1 << ". " << uniqueTimes[i] << endl;
            }

            int selectedTimeIndex;
            cout << YELLOW << "Select Time by number: " << RESET;
            cin >> selectedTimeIndex;
            if (selectedTimeIndex < 1 || selectedTimeIndex > uniqueTimesCount) {
                cout << RED << "Invalid choice. Please try again." << RESET << endl;
                system("pause");
                continue;
            }

            string selectedTime = uniqueTimes[selectedTimeIndex - 1];
            system("cls");
            cout << RED << "*********************************************" << RESET << endl;
            cout << GREEN << "\t\tAPPOINTMENTS AT " << selectedTime << RESET << endl;
            cout << RED << "*********************************************" << RESET << endl;

            bool hasAppointments = false;
            for (int i = 0; i < numofpatients; ++i) {
                if (patients[i].get_appointment_time() == selectedTime) {
                    cout << CYAN << "Patient Name: " << RESET << patients[i].get_patient_name() << endl;
                    cout << CYAN << "Doctor Name: " << RESET << patients[i].get_doctor_name() << endl;
                    cout << CYAN << "Diagnosis: " << RESET << patients[i].get_patient_diagnosis() << endl;
                    cout << RED << "------------------------------" << RESET << endl;
                    hasAppointments = true;
                }
            }

            if (!hasAppointments) {
                cout << RED << "No appointments available at this time." << RESET << endl;
            }
            system("pause");
            continue;
        }

        // Sorting based on choice 2
        if (choice == 2) {
            sort(patients, patients + numofpatients, [](const Patient& a, const Patient& b) {
                return a.get_patient_name() < b.get_patient_name();
            });

            system("cls");
            cout << RED << "*********************************************" << RESET << endl;
            cout << GREEN << "\tSORTED APPOINTMENTS BY PATIENT NAME" << RESET << endl;
            cout << RED << "*********************************************" << RESET << endl;

            if (numofpatients == 0) {
                cout << RED << "No appointments available." << RESET << endl;
            } else {
                for (int i = 0; i < numofpatients; ++i) {
                    cout << CYAN << "Doctor Name: " << RESET << patients[i].get_doctor_name() << endl;
                    cout << CYAN << "Patient Name: " << RESET << patients[i].get_patient_name() << endl;
                    cout << CYAN << "Time: " << RESET << patients[i].get_appointment_time() << endl;
                    cout << CYAN << "Diagnosis: " << RESET << patients[i].get_patient_diagnosis() << endl;
                    cout << RED << "------------------------------" << RESET << endl;
                }
            }
            system("pause");
        }
    }
}


int main() {
	bool isFirstTime = true; // Flag to check if it's the first time running the program
    // Show the welcome screen only if it's the first time
    if (isFirstTime) {
        showWelcomeScreen();
        isFirstTime = false; // Update the flag after showing the welcome screen
    }
    int choice;
    int invalidChoiceCount = 0; // Counter for invalid choices

    do {
        showMainMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            inputPatientData();
            invalidChoiceCount = 0; // Reset counter for invalid choices
        } else if (choice == 2) {
            showPatientData();
            invalidChoiceCount = 0; // Reset counter for invalid choices
        }else if (choice == 3) {
			showAppointments();
            invalidChoiceCount = 0; // Reset counter for invalid choices
        }else if (choice == 4) {
    		manageData();
		    invalidChoiceCount = 0; // Reset counter for invalid choices
		} else if (choice == 6) {
            cout << YELLOW << "Exiting..." << RESET << endl;
			cout << GREEN << "*****************************************************************" << RESET << endl;
			cout << GREEN << "*                                                               *" << RESET << endl;
			cout << GREEN << "*                    Thank you for using                        *" << RESET << endl;
			cout << GREEN << "*                 Healthcare Management System                  *" << RESET << endl;
			cout << GREEN << "*                                                               *" << RESET << endl;
			cout << GREEN << "*                         Developed By:                         *" << RESET << endl;
			cout << GREEN << "* "<< CYAN <<"        Muhammad Hammad (2023-uam-2046)   "<< GREEN <<"                    *" << RESET << endl;
			cout << GREEN << "* "<< CYAN <<"                                          "<< GREEN <<"                    *" << RESET << endl;
			cout << GREEN << "*****************************************************************" << RESET << endl;
			system("pause");
			break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
            system("pause");
            invalidChoiceCount++;
            if (invalidChoiceCount >= 3) {
                cout << "Too many invalid attempts. Exiting..." << endl;
                break;
            }
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    } while (true);

    return 0;
}
