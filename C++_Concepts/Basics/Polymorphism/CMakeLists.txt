cmake_minimum_required(VERSION 3.10)
project(Polymorpishm CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_NAME PolymorphismDemo)

set(PROJECT_SOURCES "src/PolymorphismDemo.cpp")
include_directories(include)
add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCES})
