#include "CanBusDriver_Singleton.hpp"



CanBusDriver* CanBusDriver::s_instance = nullptr;


CanBusDriver::CanBusDriver() {
    // Initialization logic for the hardware should occur here.
    std::cout << "[CAN Bus Driver] Initializing Hardware..." << std::endl;
    initialized_ = true;
    std::cout << "[CAN Bus Driver] Ready." << std::endl;
}

void CanBusDriver::initialize() {
    if (s_instance == nullptr) {
        std::cout << "\n[CanBusDriver] EXPLICIT INITIALIZATION: Creating single instance." << std::endl;
        s_instance = new CanBusDriver(); 
        std::cout << "[CanBusDriver] Instance created at address: " << s_instance << std::endl;
    } else {
        std::cout << "[CanBusDriver] Initialization skipped: Instance already exists." << std::endl;
    }
}

// Public static accessor function
CanBusDriver& CanBusDriver::get_instance() {
    
    if (s_instance == nullptr) {
        throw std::runtime_error("FATAL: CanBusDriver accessed before initialization! (s_instance is null)");
    }
    // Correctly returns the dereferenced static pointer.
    return *s_instance;
}

void CanBusDriver::transmit(const std::string& message) const {
    if (initialized_) {
        std::cout << "[CAN TX] Sending message: \"" << message << "\"" << std::endl;
    } else {
        std::cerr << "[CAN ERROR] Driver not initialized!" << std::endl;
    }
}

void CanBusDriver::receive() const {
    if (initialized_) {
        std::cout << "[CAN RX] Listening for data... (Current status: OK)" << std::endl;
    }
}
