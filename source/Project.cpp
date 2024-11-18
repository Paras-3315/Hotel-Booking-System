#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

class Login {
private:
    string LoginID, Password;
public:
    Login() : LoginID(""), Password("") {}

    void setID(string id) { LoginID = id; }
    void setPW(string pw) { Password = pw; }
    string getID() { return LoginID; }
    string getPW() { return Password; }
};

// Registration function
void registration(Login &log) {
    system("cls");
    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;
    log.setID(id);

    start:
    cout << "\tEnter a Strong Password (at least 8 characters): ";
    cin >> pw;
    if (pw.length() >= 8) {
        log.setPW(pw);
    } else {
        cout << "\tPassword must be at least 8 characters!" << endl;
        goto start;
    }

    ofstream outfile("data/login.txt", ios::app);
    if (!outfile) {
        cout << "\tError: File can't open" << endl;
    } else {
        outfile << log.getID() << " : " << log.getPW() << endl;
        cout << "\tUser Registered Successfully!" << endl;
    }
    Sleep(3000);
}

// Login function
void login() {
    system("cls");
    string id, pw;
    cout << "\tEnter LoginID: ";
    cin >> id;
    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("data/login.txt");
    if (!infile) {
        cout << "\tError opening file" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        stringstream ss(line);
        string userID, userPW;
        char delimiter;
        ss >> userID >> delimiter >> userPW;
        if (id == userID && pw == userPW) {
            found = true;
            cout << "\tLogin successful! Welcome!" << endl;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout << "\n\tIncorrect LoginID or Password\n\tplease try again" << endl;
    }
    Sleep(1000);
}

// Room class with room types and booking details
class Room {
public:
    string type;
    int pricePerHour;

    Room(string t, int pph) : type(t), pricePerHour(pph) {}
};

// Check room availability in availability.txt
bool checkRoomAvailability(string roomType, string date, int hours) {
    ifstream infile("data/availability.txt");
    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string rType, rDate;
        int rHours;
        ss >> rType >> rDate >> rHours;
        if (rType == roomType && rDate == date && rHours >= hours) {
            return false;
        }
    }
    infile.close();
    return true;
}

// Function to book room and calculate bill
void bookRoom() {
    Room single("Single", 50);
    Room doubleRoom("Double", 80);
    Room suite("Suite", 120);
    
    cout << "\nAvailable Room Types:\n";
    cout << "1. " << single.type << " - $" << single.pricePerHour << " per hour\n";
    cout << "2. " << doubleRoom.type << " - $" << doubleRoom.pricePerHour << " per hour\n";
    cout << "3. " << suite.type << " - $" << suite.pricePerHour << " per hour\n";
    
    int choice, hours;
    string date, roomType;
    cout << "\nEnter your choice of room (1-3): ";
    cin >> choice;

    if (choice == 1) roomType = single.type;
    else if (choice == 2) roomType = doubleRoom.type;
    else if (choice == 3) roomType = suite.type;
    else {
        cout << "Invalid choice! Exiting.\n";
        return;
    }

    cout << "Enter date of booking (YYYY-MM-DD): ";
    cin >> date;
    cout << "Enter duration in hours: ";
    cin >> hours;

    if (!checkRoomAvailability(roomType, date, hours)) {
        cout << "\nRoom is not available for the selected date and duration.\n";
        return;
    }

    int rate = (roomType == "Single") ? single.pricePerHour : (roomType == "Double" ? doubleRoom.pricePerHour : suite.pricePerHour);
    float totalBill = rate * hours;
    cout << "Total Bill: $" << fixed << setprecision(2) << totalBill << endl;

    // Payment process
    float payment;
    cout << "\nEnter payment amount: ";
    cin >> payment;
    if (payment >= totalBill) {
        cout << "Payment successful!" << endl;

        // Save booking details in customer.txt
        ofstream outfile("data/customer.txt", ios::app);
        if (outfile.is_open()) {
            outfile << "Room Type: " << roomType << ", Date: " << date << ", Hours: " << hours
                    << ", Total Bill: $" << totalBill << endl;
            outfile.close();
        }

        // Update availability.txt
        ofstream availFile("data/availability.txt", ios::app);
        if (availFile.is_open()) {
            availFile << roomType << " " << date << " " << hours << endl;
            availFile.close();
        }
    } else {
        cout << "Insufficient payment. Booking failed.\n";
    }
    Sleep(3000);
}

int main() {
    Login log;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To Hotel Booking System\n";
        cout << "\t1. Register\n";
        cout << "\t2. Login\n";
        cout << "\t3. Book Room\n";
        cout << "\t4. EXIT\n";
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1) {
            registration(log);
        } else if (val == 2) {
            login();
        } else if (val == 3) {
             time_t now = std::time(nullptr); 
    cout << "Current time: " << ctime(&now); 
            bookRoom();
        } else if (val == 4) {
            cout << "\nThank you for visiting our site!\nWishing you vibrant health and happiness on your journey.\n Enjoy your experience with us!";
            exit = true;
        } else {
            cout << "Invalid option. Try again.\n";
        }
        Sleep(2000);
    }

    return 0;
}