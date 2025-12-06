#include "calculator.hpp"
#include <stdexcept>

// Implements the addition function
int Calculator::Add(int a, int b) const {
    return a + b;
}

// Implements the subtraction function
int Calculator::Subtract(int a, int b) const {
    return a - b;
}

// Implements the division function with error handling
double Calculator::Divide(int a, int b) const {
    if (b == 0) {
        // Throw a standard exception if division by zero occurs
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    // Static cast to double to ensure floating-point division
    return static_cast<double>(a) / b;
}