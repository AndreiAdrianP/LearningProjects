cmake_minimum_required(VERSION 3.10)
project(RAII CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_NAME StaticFactory)

set(PROJECT_SOURCES "src/StaticFactory.cpp")
include_directories(include)
add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCES})
