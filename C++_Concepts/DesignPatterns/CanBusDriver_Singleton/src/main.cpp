#include "CanBusDriver_Singleton.hpp"
#include <iostream>
#include <stdexcept>


// Helper function representing Module A: attempts to access and use the shared resource.
void run_module_a() {
    std::cout << "\n--- Module A Logic ---" << std::endl;
    // Module A requests the single instance of the driver
    CanBusDriver& driver = CanBusDriver::get_instance();
    driver.transmit("Brake_Status_100ms_OK");
}

// Helper function representing Module B: attempts to access and use the shared resource.
void run_module_b() {
    std::cout << "\n--- Module B Logic ---" << std::endl;
    // Module B also requests the single instance of the driver
    CanBusDriver& driver = CanBusDriver::get_instance();
    driver.receive();
    driver.transmit("Headlight_Status_ON");
}

int main() {
    std::cout << "--- System Startup ---" << std::endl;
    
    CanBusDriver::initialize(); 
    
    run_module_a();
    run_module_b();

    // Proving they access the same instance:
    std::cout << "\n--- Instance Verification ---" << std::endl;
    // Get pointers to the instance via the static method from two different calls
    CanBusDriver* driver1 = &CanBusDriver::get_instance();
    CanBusDriver* driver2 = &CanBusDriver::get_instance();

    std::cout << "Address of Driver 1: " << driver1 << std::endl;
    std::cout << "Address of Driver 2: " << driver2 << std::endl;

    if (driver1 == driver2) {
        std::cout << "SUCCESS: Both modules access the same unique CAN Bus Driver instance." << std::endl;
    }

    return 0;
}