#pragma once
#include <string>
#include <stdexcept>
#include <utility>

enum class VehicleType { Bike, Car, Truck };

inline std::string vehicleTypeToString(VehicleType t) {
    switch (t) {
        case VehicleType::Bike:  return "BIKE";
        case VehicleType::Car:   return "CAR";
        case VehicleType::Truck: return "TRUCK";
    }
    return "CAR";
}

inline VehicleType vehicleTypeFromString(std::string s) {
    for (char& c : s) c = (char)std::toupper((unsigned char)c);
    if (s == "BIKE")  return VehicleType::Bike;
    if (s == "CAR")   return VehicleType::Car;
    if (s == "TRUCK") return VehicleType::Truck;
    throw std::invalid_argument("Invalid vehicle type: " + s);
}

class Vehicle {
    std::string plateNo;
    VehicleType type;
public:
    Vehicle(std::string plate, VehicleType t) : plateNo(std::move(plate)), type(t) {}
    const std::string& getPlateNo() const { return plateNo; }
    VehicleType getType() const { return type; }
};

struct Ticket {
    std::string ticketId;
    std::string plateNo;
    VehicleType vehicleType = VehicleType::Car;
    int slotId = -1;
    long long entryEpochMs = 0;
};

struct Session {
    std::string ticketId;
    std::string plateNo;
    VehicleType vehicleType = VehicleType::Car;
    int slotId = -1;

    long long entryEpochMs = 0;
    long long exitEpochMs = 0;

    int durationMinutes = 0;
    double fee = 0.0;
};

class ParkingSlot {
    int slotId = -1;
    VehicleType allowedType = VehicleType::Car;
    bool occupied = false;

    std::string currentPlate;
    VehicleType currentType = VehicleType::Car;

public:
    ParkingSlot(int id, VehicleType allowed) : slotId(id), allowedType(allowed) {}

    int getId() const { return slotId; }
    VehicleType getAllowedType() const { return allowedType; }

    bool isOccupied() const { return occupied; }
    const std::string& getCurrentPlate() const { return currentPlate; }
    VehicleType getCurrentType() const { return currentType; }

    bool canFit(VehicleType t) const { return (!occupied) && (t == allowedType); }

    void park(const Vehicle& v) {
        if (occupied) throw std::runtime_error("Slot already occupied");
        if (v.getType() != allowedType) throw std::runtime_error("Vehicle type not allowed in this slot");
        occupied = true;
        currentPlate = v.getPlateNo();
        currentType = v.getType();
    }

    void vacate() {
        if (!occupied) throw std::runtime_error("Slot already free");
        occupied = false;
        currentPlate.clear();
    }
};
