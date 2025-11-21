#include "StaticFactory.hpp"
#include <iostream>

void demonstrate_vehicle_use(VehicleFactory::VehicleType type) {
    std::cout << "\n--- Requesting Vehicle Type: " 
              << (type == VehicleFactory::VehicleType::CAR ? "CAR" : 
                  (type == VehicleFactory::VehicleType::TRUCK ? "TRUCK" : "UNKNOWN")) 
              << " ---" << std::endl;
    
    // Client calls the static factory method. It doesn't need to know 'new Car()' or 'new Truck()'.
    std::unique_ptr<Vehicle> my_vehicle = VehicleFactory::createVehicle(type);

    if (my_vehicle) {
        std::cout << "Factory created a: " << my_vehicle->getType() << std::endl;
        my_vehicle->drive();
    } else {
        std::cout << "Vehicle creation failed." << std::endl;
    }
}

int main() {
    std::cout << "--- Static Factory Method Demonstration ---" << std::endl;

    // 1. Create a Car
    demonstrate_vehicle_use(VehicleFactory::VehicleType::CAR);

    // 2. Create a Truck
    demonstrate_vehicle_use(VehicleFactory::VehicleType::TRUCK);
    
    // 3. Request an unimplemented type
    demonstrate_vehicle_use(VehicleFactory::VehicleType::MOTORCYCLE);

    // The created objects (my_vehicle) are automatically managed by std::unique_ptr 
    // and correctly deleted when they go out of scope.

    std::cout << "\n--- Demonstration Complete ---" << std::endl;
    return 0;
}