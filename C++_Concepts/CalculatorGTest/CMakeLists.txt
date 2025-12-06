cmake_minimum_required(VERSION 3.10)
project(CalculatorApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the option to control the building of tests.
# This allows the user to run: cmake -DBUILD_TESTING=OFF ..
option(BUILD_TESTING "Build the Google Test unit tests" ON)

# ----------------------------------------------------
# 1. Core Library Setup (Always built)
# ----------------------------------------------------

# Define a static library target for the calculator source files.
add_library(calc_lib STATIC src/calculator.cpp)

# Ensure the library headers are accessible to the runner and tests.
target_include_directories(calc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# ----------------------------------------------------
# 2. Application Executable Setup
# ----------------------------------------------------

# Define the main application executable
add_executable(CalculatorRunner src/main.cpp)

# Link the executable to the library containing the logic
target_link_libraries(CalculatorRunner calc_lib)

# ----------------------------------------------------
# 3. Conditional Testing Setup (Find Package)
# ----------------------------------------------------

if(BUILD_TESTING)
    message(STATUS "Unit testing enabled. Using system-installed GTest.")

    # Find the installed GTest package. This automatically finds the 
    # configuration files placed by 'sudo apt install libgtest-dev'.
    find_package(GTest REQUIRED) 

    # ----------------------------------------------------
    # 4. Test Executable Setup
    # ----------------------------------------------------

    add_executable(run_tests tests/test_calculator.cpp)

    # Link to the production code library and the GTest main target.
    # GTest::gtest_main automatically includes the headers and necessary libraries.
    target_link_libraries(run_tests 
        calc_lib         
        GTest::gtest_main
    )

else()
    message(STATUS "Unit testing is disabled.")
endif()