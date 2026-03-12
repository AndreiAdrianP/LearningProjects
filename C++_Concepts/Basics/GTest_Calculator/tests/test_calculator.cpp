#include "gtest/gtest.h"
#include "calculator.hpp" 
#include <stdexcept>

// ----------------------------------------------------------------------
// 1. Test Fixture Setup (TEST_F)
// ----------------------------------------------------------------------

class CalculatorTest : public ::testing::Test {
protected:
    // This object is created before every single test method.
    Calculator calc; 

    // Optional: Setup method run before each test
    void SetUp() override {
        // You could initialize calc here, but default constructor is fine.
    }

    // Optional: Teardown method run after each test
    void TearDown() override {
        // Clean up resources if necessary
    }
};

// ----------------------------------------------------------------------
// 2. Unit Tests
// ----------------------------------------------------------------------

// Test case for the Add method
TEST_F(CalculatorTest, HandlesPositiveAddition) {
    // We use the 'calc' object created in the fixture.
    // ASSERT_EQ is a fatal assertion: if it fails, the test stops immediately.
    ASSERT_EQ(5, calc.Add(2, 3));
}

// Test case for negative numbers
TEST_F(CalculatorTest, HandlesNegativeSubtraction) {
    // EXPECT_EQ is a non-fatal assertion: if it fails, the test continues.
    EXPECT_EQ(-1, calc.Subtract(4, 5));
    EXPECT_EQ(10, calc.Subtract(5, -5)); 
}

// Test case to ensure floating point division is accurate
TEST_F(CalculatorTest, HandlesFloatingPointDivision) {
    // ASSERT_NEAR checks if the two values are close within a tolerance (delta).
    ASSERT_NEAR(2.5, calc.Divide(5, 2), 0.001); 
}

// Test case for the division by zero error handling
TEST_F(CalculatorTest, ThrowsExceptionOnDivideByZero) {
    // ASSERT_THROW asserts that the code inside the block throws a specific exception.
    ASSERT_THROW(calc.Divide(10, 0), std::invalid_argument);
}

// ----------------------------------------------------------------------
// 3. Test Runner Main (Included for simplicity, often external in large projects)
// ----------------------------------------------------------------------

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}