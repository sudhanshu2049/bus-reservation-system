#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Passenger {
    string name;
    string phone;
    string email;
    int seat_number;
};

class Route {
protected:
    string start_city;
    string end_city;
    string checkpoints[3];
    int checkpoint_count;
public:
    Route() {
        start_city = "Unknown";
        end_city = "Unknown";
        checkpoint_count = 0;
    }
    Route(string start, string end, string cp[], int cp_count) {
        start_city = start;
        end_city = end;
        checkpoint_count = cp_count;
        for (int i = 0; i < cp_count; i++) {
            checkpoints[i] = cp[i];
        }
    }
    void showRoute() {
        cout << "Route: " << start_city << " to " << end_city << endl;
        cout << "Checkpoints: ";
        for (int i = 0; i < checkpoint_count; i++) {
            cout << checkpoints[i];
            if (i < checkpoint_count - 1) cout << " -> ";
        }
        cout << endl;
    }
};

class Bus : public Route {
private:
    static int total_buses;
    int bus_number;
    int seats[30];
    string driver_name;
    Passenger passengers[30];
public:
    Bus() : Route() {
        bus_number = 0;
        driver_name = "Unknown";
        for (int i = 0; i < 30; i++) {
            seats[i] = 0;
            passengers[i] = {"", "", "", 0};
        }
        total_buses++;
    }
    Bus(int num, string driver, string start, string end, string cp[], int cp_count)
        : Route(start, end, cp, cp_count) {
        bus_number = num;
        driver_name = driver;
        for (int i = 0; i < 30; i++) {
            seats[i] = 0;
            passengers[i] = {"", "", "", 0};
        }
        total_buses++;
    }
    void setBusNumber(int num) {
        bus_number = num;
    }
    void reserveSeat(int seat, string name, string phone, string email) {
        if (seat < 1 || seat > 30) {
            cout << "Invalid seat number! Choose between 1-30." << endl;
            return;
        }
        if (seats[seat - 1] == 1) {
            cout << "Seat " << seat << " is already reserved!" << endl;
        } else {
            seats[seat - 1] = 1;
            passengers[seat - 1] = {name, phone, email, seat};
            cout << "Seat " << seat << " reserved successfully for " << name << "." << endl;
            cout << "\nReservation Confirmation:\n";
            cout << "Passenger Name: " << name << endl;
            cout << "Phone: " << phone << endl;
            cout << "Email: " << email << endl;
            cout << "Bus: " << bus_number << " (" << start_city << " to " << end_city << ")" << endl;
            cout << "Driver: " << driver_name << endl;
            cout << "Seat Booked: " << seat << endl;
        }
    }
    void cancelSeat(int seat) {
        if (seat < 1 || seat > 30) {
            cout << "Invalid seat number! Choose between 1-30." << endl;
            return;
        }
        if (seats[seat - 1] == 0) {
            cout << "Seat " << seat << " is not reserved!" << endl;
        } else {
            seats[seat - 1] = 0;
            cout << "Reservation for seat " << seat << " (Passenger: " << passengers[seat - 1].name << ") cancelled." << endl;
            passengers[seat - 1] = {"", "", "", 0};
        }
    }
    void showSeats() {
        cout << "\nBus " << bus_number << " (" << start_city << " to " << end_city << ") - Seats:\n";
        for (int i = 0; i < 30; i++) {
            if (seats[i] == 1)
                cout << "[X] ";
            else
                cout << "[" << (i + 1) << "] ";
            if ((i + 1) % 10 == 0)
                cout << endl;
        }
        cout << "\nReserved Seats Details:\n";
        bool hasReservations = false;
        for (int i = 0; i < 30; i++) {
            if (seats[i] == 1) {
                hasReservations = true;
                cout << "Seat " << passengers[i].seat_number << ": " << passengers[i].name
                     << ", Phone: " << passengers[i].phone << ", Email: " << passengers[i].email << endl;
            }
        }
        if (!hasReservations) {
            cout << "No seats reserved yet." << endl;
        }
        cout << endl;
    }
    void showBusDetails() {
        cout << "\nBus Number: " << bus_number << endl;
        cout << "Driver: " << driver_name << endl;
        showRoute();
        showSeats();
    }
    static void showTotalBuses() {
        cout << "Total buses in system: " << total_buses << endl;
    }
    int checkSeatAvailability() {
        int available_seats = 0;
        for (int i = 0; i < 30; i++) {
            if (seats[i] == 0) {
                available_seats++;
            }
        }
        return available_seats;
    }
    void showPassengerList() {
        cout << "\nPassenger List for Bus " << bus_number << " (" << start_city << " to " << end_city << "):\n";
        bool hasReservations = false;
        for (int i = 0; i < 30; i++) {
            if (seats[i] == 1) {
                hasReservations = true;
                cout << "Seat " << passengers[i].seat_number << ": " << passengers[i].name
                     << ", Phone: " << passengers[i].phone << ", Email: " << passengers[i].email << endl;
            }
        }
        if (!hasReservations) {
            cout << "No passengers reserved on this bus." << endl;
        }
        cout << endl;
    }
    bool searchPassenger(string search_name, string& found_details) {
        for (int i = 0; i < 30; i++) {
            if (seats[i] == 1 && passengers[i].name == search_name) {
                found_details = "Bus: " + to_string(bus_number) + " (" + start_city + " to " + end_city + ")\n" +
                                "Seat: " + to_string(passengers[i].seat_number) + "\n" +
                                "Name: " + passengers[i].name + "\n" +
                                "Phone: " + passengers[i].phone + "\n" +
                                "Email: " + passengers[i].email + "\n";
                return true;
            }
        }
        return false;
    }
};

int Bus::total_buses = 0;

int main() {
    string route1_cp[] = {"Panipat", "Karnal", "Ambala"};
    string route2_cp[] = {"Agra", "Mathura", "Faridabad"};
    string route3_cp[] = {"Agra", "Kanpur"};
    string route4_cp[] = {"Surat", "Vadodara", "Ahmedabad"};
    string route5_cp[] = {"Hyderabad", "Nagpur", "Bhopal"};
    string route6_cp[] = {"Varanasi", "Patna"};
    string route7_cp[] = {"Nagpur", "Vijayawada"};
    string route8_cp[] = {"Udaipur", "Jaipur"};
    string route9_cp[] = {"Nagpur", "Bhopal"};
    string route10_cp[] = {"Surat", "Vadodara"};

    Bus buses[10] = {
        Bus(1, "Ravi Kumar", "Delhi", "Chandigarh", route1_cp, 3),
        Bus(2, "Anil Sharma", "Delhi", "Jaipur", route2_cp, 3),
        Bus(3, "Vikram Singh", "Delhi", "Lucknow", route3_cp, 2),
        Bus(4, "Suresh Patel", "Delhi", "Mumbai", route4_cp, 3),
        Bus(5, "Rahul Verma", "Delhi", "Bangalore", route5_cp, 3),
        Bus(6, "Amit Gupta", "Delhi", "Kolkata", route6_cp, 2),
        Bus(7, "Kiran Reddy", "Delhi", "Chennai", route7_cp, 2),
        Bus(8, "Neha Sharma", "Delhi", "Ahmedabad", route8_cp, 2),
        Bus(9, "Pooja Desai", "Delhi", "Hyderabad", route9_cp, 2),
        Bus(10, "Rohan Mehta", "Delhi", "Pune", route10_cp, 2)
    };

    int choice, bus_no, return_bus_no, seat_no, return_seat_no;
    string name, phone, email, search_name;

    while (true) {
        cout << "\n=== Bus Reservation System ===\n";
        cout << "1. Reserve a seat\n";
        cout << "2. Cancel a reservation\n";
        cout << "3. Show bus details\n";
        cout << "4. Show total buses\n";
        cout << "5. Show route information\n";
        cout << "6 Book seat with return ticket\n";
        cout << "7 Check seat availability\n";
        cout << "8 Show passenger list\n";
        cout << "9 Search passenger by name\n";
        cout << "10 Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number." << endl;
            cout << "Press Enter to continue...";
            cin.get();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            cout << "Enter bus number (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> bus_no;
            if (bus_no < 1 || bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            cout << "\nSelected Bus Route:\n";
            buses[bus_no - 1].showRoute();
            cout << endl;
            cout << "Enter seat number (1-30): ";
            cin >> seat_no;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter passenger name: ";
            getline(cin, name);
            cout << "Enter passenger phone number: ";
            getline(cin, phone);
            cout << "Enter passenger email: ";
            getline(cin, email);
            buses[bus_no - 1].reserveSeat(seat_no, name, phone, email);
            cout << "Press Enter to continue...";
            cin.get();
            break;

        case 2:
            cout << "Enter bus number (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> bus_no;
            if (bus_no < 1 || bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            cout << "Enter seat number (1-30): ";
            cin >> seat_no;
            buses[bus_no - 1].cancelSeat(seat_no);
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;

        case 3:
            for (int i = 0; i < 10; i++) {
                buses[i].showBusDetails();
            }
            cout << "Press Enter to continue...";
            cin.get();
            break;

        case 4:
            Bus::showTotalBuses();
            cout << "Press Enter to continue...";
            cin.get();
            break;

        case 5:
            cout << "Enter bus number (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> bus_no;
            if (bus_no < 1 || bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            buses[bus_no - 1].showRoute();
            cout << "Press Enter to continue...";
            cin.get();
            break;

       

        case 6:
            cout << "\n=== Book Outbound Ticket ===\n";
            cout << "Enter bus number for outbound trip (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> bus_no;
            if (bus_no < 1 || bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            cout << "\nOutbound Bus Route:\n";
            buses[bus_no - 1].showRoute();
            cout << endl;
            cout << "Enter seat number for outbound trip (1-30): ";
            cin >> seat_no;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter passenger name: ";
            getline(cin, name);
            cout << "Enter passenger phone number: ";
            getline(cin, phone);
            cout << "Enter passenger email: ";
            getline(cin, email);
            buses[bus_no - 1].reserveSeat(seat_no, name, phone, email);
            cout << "\n=== Book Return Ticket ===\n";
            cout << "Enter bus number for return trip (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> return_bus_no;
            if (return_bus_no < 1 || return_bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            cout << "\nReturn Bus Route:\n";
            buses[return_bus_no - 1].showRoute();
            cout << endl;
            cout << "Enter seat number for return trip (1-30): ";
            cin >> return_seat_no;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            buses[return_bus_no - 1].reserveSeat(return_seat_no, name, phone, email);
            cout << "Press Enter to continue...";
            cin.get();
            break;

        case 7:
            cout << "Enter bus number (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> bus_no;
            if (bus_no < 1 || bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            cout << "\nBus " << bus_no << " Route:\n";
            buses[bus_no - 1].showRoute();
            cout << "Has " << buses[bus_no - 1].checkSeatAvailability() << " seats available out of 30." << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;

        case 8:
            cout << "Enter bus number (1 for Delhi-Chandigarh, 2 for Delhi-Jaipur, 3 for Delhi-Lucknow, "
                 << "4 for Delhi-Mumbai, 5 for Delhi-Bangalore, 6 for Delhi-Kolkata, 7 for Delhi-Chennai, "
                 << "8 for Delhi-Ahmedabad, 9 for Delhi-Hyderabad, 10 for Delhi-Pune): ";
            cin >> bus_no;
            if (bus_no < 1 || bus_no > 10) {
                cout << "Invalid bus number! Choose between 1 and 10." << endl;
                cout << "Press Enter to continue...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }
            buses[bus_no - 1].showPassengerList();
            cout << "Press Enter to continue...";
            cin.get();
            break;

        case 9: {
            cout << "Enter passenger name to search: ";
            getline(cin, search_name);
            bool found = false;
            string found_details;
            for (int i = 0; i < 10; i++) {
                if (buses[i].searchPassenger(search_name, found_details)) {
                    found = true;
                    cout << "\nPassenger found:\n" << found_details;
                }
            }
            if (!found) {
                cout << "Passenger not found." << endl;
            }
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }
        case 10:
        cout << "Thank you for using the Bus Reservation System!\n";
        break;

        default:
            cout << "Invalid choice! Please try again." << endl;
            cout << "Press Enter to continue...";
            cin.get();
            break;
        }

        if (choice == 10) {
            break;
        }
    }

    return 0;
}