#pragma once
#include <iostream>
#include <string>
#include <memory> // For std::unique_ptr

// --- 1. Base Product Interface ---
class Vehicle {
public:
    virtual ~Vehicle() = default; // Virtual destructor is crucial for base classes
    virtual void drive() const = 0;
    virtual std::string getType() const = 0;
};

// --- 2. Concrete Product Classes ---

class Car : public Vehicle {
public:
    void drive() const override {
        std::cout << "[Car] Driving smoothly on the road." << std::endl;
    }
    std::string getType() const override {
        return "Car";
    }
};

class Truck : public Vehicle {
public:
    void drive() const override {
        std::cout << "[Truck] Hauling heavy cargo over the highway." << std::endl;
    }
    std::string getType() const override {
        return "Truck";
    }
};

// --- 3. Static Factory Class ---
class VehicleFactory {
public:
    enum class VehicleType {
        CAR,
        TRUCK,
        MOTORCYCLE // Placeholder for future expansion
    };


    static std::unique_ptr<Vehicle> createVehicle(VehicleType type) {
        switch (type) {
            case VehicleType::CAR:
                // Instantiates the concrete class and returns it as the base type.
                return std::make_unique<Car>();
            case VehicleType::TRUCK:
                return std::make_unique<Truck>();
            case VehicleType::MOTORCYCLE:
                std::cerr << "[Factory Error] Motorcycle production not yet implemented!" << std::endl;
                return nullptr;
            default:
                std::cerr << "[Factory Error] Unknown vehicle type requested." << std::endl;
                return nullptr;
        }
    }

private:
    // Factory itself should not be instantiable (enforced by private constructor)
    VehicleFactory() = delete; 
    ~VehicleFactory() = delete;
};