#pragma once

#include <iostream>
#include <string>

// Represents a unique, shared hardware resource (like a CAN Bus controller).
class CanBusDriver {
public:
    static void initialize();
    // Static method to access the single instance.
    static CanBusDriver& get_instance();

    // Core functionality method
    void transmit(const std::string& message) const;
    void receive() const;

private:
    static CanBusDriver* s_instance;
    // Private constructor ensures the class cannot be instantiated externally.
    CanBusDriver(); 
   

    // Delete copy and move operations to enforce the singleton constraint.
    CanBusDriver(const CanBusDriver&) = delete;
    CanBusDriver& operator=(const CanBusDriver&) = delete;
    CanBusDriver(CanBusDriver&&) = delete;
    CanBusDriver& operator=(CanBusDriver&&) = delete;

    bool initialized_ = false;
};