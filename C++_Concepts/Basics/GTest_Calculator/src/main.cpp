#include "calculator.hpp"
#include <iostream>
#include <stdexcept>

int main() {
    Calculator calc;
    int a = 10;
    int b = 5;

    std::cout << "--- Calculator Demo ---" << std::endl;
    std::cout << "Inputs: a=" << a << ", b=" << b << std::endl;

    // Test Add
    int sum = calc.Add(a, b);
    std::cout << "Add (" << a << " + " << b << "): " << sum << std::endl;

    // Test Subtract
    int difference = calc.Subtract(a, b);
    std::cout << "Subtract (" << a << " - " << b << "): " << difference << std::endl;

    // Test Divide (Success)
    try {
        double quotient = calc.Divide(a, b);
        std::cout << "Divide (" << a << " / " << b << "): " << quotient << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Division Error: " << e.what() << std::endl;
    }
    
    // Test Divide (Error)
    int c = 0;
    try {
        std::cout << "Testing Division by Zero (" << a << " / " << c << "): ";
        calc.Divide(a, c);
    } catch (const std::invalid_argument& e) {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }
    
    return 0;
}