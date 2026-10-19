
#include <iostream>
#include <string>
#include <queue>
#include <limits>
using namespace std;

// Patient information
class Patient {
public:
    int id;
    string name;
    int age;
    string gender;
    string disease;
    string phone;
    Patient* next;

    Patient(int i, string n, int a, string g,
            string d, string p) {
        id = i;
        name = n;
        age = a;
        gender = g;
        disease = d;
        phone = p;
        next = nullptr;
    }
};

// Hospital Patient Management System
class Hospital {
private:
    Patient* head;
    queue<int> normalQueue;
    queue<int> emergencyQueue;

    // Find patient by ID
    Patient* findPatient(int id) {
        Patient* temp = head;

        while (temp != nullptr) {
            if (temp->id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

public:
    Hospital() {
        head = nullptr;
    }

    // Add a new patient
    void addPatient() {
        int id, age, type;
        string name, gender, disease, phone;

        cout << "\nEnter Patient ID: ";
        cin >> id;

        if (findPatient(id) != nullptr) {
            cout << "Patient ID already exists!\n";
            return;
        }

        cout << "Enter Name: ";
        getline(cin >> ws, name);

        cout << "Enter Age: ";
        cin >> age;

        if (age < 0) {
            cout << "Invalid age!\n";
            return;
        }

        cout << "Enter Gender: ";
        getline(cin >> ws, gender);

        cout << "Enter Disease: ";
        getline(cin >> ws, disease);

        cout << "Enter Phone Number: ";
        getline(cin >> ws, phone);

        Patient* newPatient = new Patient(
            id, name, age, gender, disease, phone
        );

        // Insert at end of linked list
        if (head == nullptr) {
            head = newPatient;
        } else {
            Patient* temp = head;
            while (temp->next != nullptr)
                temp = temp->next;

            temp->next = newPatient;
        }

        cout << "Patient type (1 = Normal, 2 = Emergency): ";
        cin >> type;

        if (type == 2) {
            emergencyQueue.push(id);
            cout << "Emergency patient registered successfully!\n";
        } else {
            normalQueue.push(id);
            cout << "Normal patient registered successfully!\n";
        }
    }

    // Display all patients
    void displayPatients() {
        if (head == nullptr) {
            cout << "\nNo patient records found.\n";
            return;
        }

        Patient* temp = head;

        cout << "\n========== PATIENT RECORDS ==========\n";

        while (temp != nullptr) {
            cout << "\nPatient ID : " << temp->id;
            cout << "\nName       : " << temp->name;
            cout << "\nAge        : " << temp->age;
            cout << "\nGender     : " << temp->gender;
            cout << "\nDisease    : " << temp->disease;
            cout << "\nPhone      : " << temp->phone;
            cout << "\n-------------------------------------\n";

            temp = temp->next;
        }
    }

    // Search patient
    void searchPatient() {
        int id;
        cout << "\nEnter Patient ID to search: ";
        cin >> id;

        Patient* p = findPatient(id);

        if (p == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        cout << "\nPatient Found!\n";
        cout << "ID      : " << p->id << '\n';
        cout << "Name    : " << p->name << '\n';
        cout << "Age     : " << p->age << '\n';
        cout << "Gender  : " << p->gender << '\n';
        cout << "Disease : " << p->disease << '\n';
        cout << "Phone   : " << p->phone << '\n';
    }

    // Update patient information
    void updatePatient() {
        int id;
        cout << "\nEnter Patient ID to update: ";
        cin >> id;

        Patient* p = findPatient(id);

        if (p == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        cout << "Enter New Name: ";
        getline(cin >> ws, p->name);

        cout << "Enter New Age: ";
        cin >> p->age;

        if (p->age < 0) {
            cout << "Invalid age. Update cancelled.\n";
            return;
        }

        cout << "Enter New Gender: ";
        getline(cin >> ws, p->gender);

        cout << "Enter New Disease: ";
        getline(cin >> ws, p->disease);

        cout << "Enter New Phone: ";
        getline(cin >> ws, p->phone);

        cout << "Patient record updated successfully!\n";
    }

    // Discharge patient / delete record
    void dischargePatient() {
        int id;
        cout << "\nEnter Patient ID to discharge: ";
        cin >> id;

        Patient* temp = head;
        Patient* prev = nullptr;

        while (temp != nullptr && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Patient not found!\n";
            return;
        }

        if (prev == nullptr)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Patient discharged and record deleted.\n";
    }

    // Sort patient records by ID (ascending)
    void sortPatients() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Not enough records to sort.\n";
            return;
        }

        for (Patient* i = head; i->next != nullptr; i = i->next) {
            for (Patient* j = i->next; j != nullptr; j = j->next) {
                if (i->id > j->id) {
                    swap(i->id, j->id);
                    swap(i->name, j->name);
                    swap(i->age, j->age);
                    swap(i->gender, j->gender);
                    swap(i->disease, j->disease);
                    swap(i->phone, j->phone);
                }
            }
        }

        cout << "Patients sorted by ID successfully!\n";
    }

    // Serve next patient from a queue
    void serveNextPatient(bool emergency) {
        queue<int>& q = emergency ? emergencyQueue : normalQueue;

        while (!q.empty()) {
            int id = q.front();
            q.pop();

            Patient* p = findPatient(id);

            // Ignore patients already discharged
            if (p == nullptr)
                continue;

            cout << "\nNow serving patient:\n";
            cout << "ID: " << p->id << '\n';
            cout << "Name: " << p->name << '\n';
            cout << "Disease: " << p->disease << '\n';
            return;
        }

        cout << "No patients waiting in this queue.\n";
    }

    // Display waiting queue
    void displayQueue(bool emergency) {
        queue<int> q = emergency ? emergencyQueue : normalQueue;
        bool found = false;

        cout << (emergency
            ? "\nEmergency Waiting Queue:\n"
            : "\nNormal Waiting Queue:\n");

        while (!q.empty()) {
            int id = q.front();
            q.pop();

            Patient* p = findPatient(id);

            if (p != nullptr) {
                cout << "ID: " << p->id
                     << " | Name: " << p->name << '\n';
                found = true;
            }
        }

        if (!found)
            cout << "No patients waiting.\n";
    }

    // Free linked-list memory
    ~Hospital() {
        while (head != nullptr) {
            Patient* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    Hospital hospital;
    int choice;

    do {
        cout << "\n\n====================================";
        cout << "\n HOSPITAL PATIENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Patient";
        cout << "\n2. Display All Patients";
        cout << "\n3. Search Patient";
        cout << "\n4. Update Patient";
        cout << "\n5. Discharge Patient";
        cout << "\n6. Sort Patients by ID";
        cout << "\n7. Serve Emergency Patient";
        cout << "\n8. Serve Normal Patient";
        cout << "\n9. Display Emergency Queue";
        cout << "\n10. Display Normal Queue";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                hospital.addPatient();
                break;
            case 2:
                hospital.displayPatients();
                break;
            case 3:
                hospital.searchPatient();
                break;
            case 4:
                hospital.updatePatient();
                break;
            case 5:
                hospital.dischargePatient();
                break;
            case 6:
                hospital.sortPatients();
                break;
            case 7:
                hospital.serveNextPatient(true);
                break;
            case 8:
                hospital.serveNextPatient(false);
                break;
            case 9:
                hospital.displayQueue(true);
                break;
            case 10:
                hospital.displayQueue(false);
                break;
            case 0:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
