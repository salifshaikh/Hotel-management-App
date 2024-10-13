#include <iostream>
#include <fstream>
#include <cstring>  

using namespace std;

struct Room {
    int roomNumber;
    char guestName[50];
    bool isBooked;
};

void reserveRoom(Room rooms[], int totalRooms) {
    int roomNum;
    cout << "Enter room number (1-" << totalRooms << "): ";
    cin >> roomNum;

    if (roomNum < 1 || roomNum > totalRooms) {
        cout << "Invalid room number! Please try again.\n";
        return;
    }

    if (rooms[roomNum - 1].isBooked) {
        cout << "Room " << roomNum << " is already booked.\n";
    } else {
        cout << "Enter guest name: ";
        cin.ignore();  // To handle leftover newline
        cin.getline(rooms[roomNum - 1].guestName, 50);
        rooms[roomNum - 1].isBooked = true;
        cout << "Room " << roomNum << " has been successfully booked.\n";
    }
}

void displayEmptyRooms(Room rooms[], int totalRooms) {
    int emptyCount = 0;
    cout << "List of empty rooms:\n";
    for (int i = 0; i < totalRooms; i++) {
        if (!rooms[i].isBooked) {
            emptyCount++;
            cout << "Room " << rooms[i].roomNumber << " is empty.\n";
        }
    }
    if (emptyCount == 0) {
        cout << "No empty rooms available.\n";
    } else {
        cout << "Total empty rooms: " << emptyCount << endl;
    }
}

void writeToFile(Room rooms[], int totalRooms, const char* filename) {
    ofstream file;
    file.open(filename);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    int recordCount = 0;
    for (int i = 0; i < totalRooms && recordCount < 5; i++) {
        if (rooms[i].isBooked) {
            file << "Room Number: " << rooms[i].roomNumber
                 << ", Guest Name: " << rooms[i].guestName << endl;
            recordCount++;
        }
    }

    file.close();
    cout << "Records written to file successfully.\n";
}

int main() {
    const int totalRooms = 10;
    Room rooms[totalRooms];

    for (int i = 0; i < totalRooms; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].isBooked = false;
        strcpy(rooms[i].guestName, "N/A");
    }

    int choice;
    const char* filename = "bookings.txt";

    do {
        cout << "\nHotel Management System\n";
        cout << "1. Reserve a Room\n";
        cout << "2. Display Empty Rooms\n";
        cout << "3. Write Records to File\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                reserveRoom(rooms, totalRooms);
                break;
            case 2:
                displayEmptyRooms(rooms, totalRooms);
                break;
            case 3:
                writeToFile(rooms, totalRooms, filename);
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
