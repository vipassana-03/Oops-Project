#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>

using namespace std;
static long long nowMs() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}
class ParkingLot {
    struct Ticket {
        string ticketId;
        string plate;
        int slotId;
        long long entryMs;
    };
    int nSlots;
    vector<bool> occupied;
    unordered_map<string, Ticket> activeTickets;
    int nextTicketNo = 1; //Should be edited, technically issuing ticket numbers sequentially is bad Cybersecurity practice.
public:
    ParkingLot(int slots) : nSlots(slots), occupied(slots, false) {} //Constructor to actually create parking lots
    string park(const string& plate) { //const string& plate basically means that even though we're accessing plate directly and not through a copy, we can't modify it.
        int slot = -1;
        for (int i = 0; i < nSlots; i++) {
            if (!occupied[i]) { slot = i; break; }
        }
        if (slot == -1) return "";
        occupied[slot] = true;
        Ticket t;
        t.ticketId = "T" + to_string(nextTicketNo++);
        t.plate = plate;
        t.slotId = slot;
        t.entryMs = nowMs();
        activeTickets[t.ticketId] = t;
        return t.ticketId;
    }
    bool unpark(const string& ticketId) {
        auto it = activeTickets.find(ticketId);
        if (it == activeTickets.end()) return false;
        occupied[it->second.slotId] = false;
        activeTickets.erase(it);
        return true;
    }
    void status() const {
        int freeCount = 0;
        for (bool x : occupied) if (!x) freeCount++;

        cout << "Total slots: " << nSlots
             << " | Free: " << freeCount
             << " | Occupied: " << (nSlots - freeCount) << "\n";
    }
};

int main() {
    ParkingLot lot(2); //Should probably take input from the user in order to find out how large their parking lot is, or atleast hold 10 in a macro so that it's editable
    int choice = 0;

    while (choice != 4) {
        cout << "\n1) Park\n2) Unpark\n3) Status\n4) End\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string plate;
                cout << "Enter License Plate: ";
                cin >> plate;
                string ticketId = lot.park(plate);
                if (ticketId == "") cout << "Parking full.\n";
                else cout << "Parked. Ticket: " << ticketId << "\n";
                break;
            }
            case 2: {
                string ticketId;
                cout << "Enter Ticket ID: ";
                cin >> ticketId;
                if (lot.unpark(ticketId)) cout << "Unparked.\n";
                else cout << "Invalid ticket.\n";
                break;
            }
            case 3:
                lot.status();
                break;
            case 4:
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }
}
