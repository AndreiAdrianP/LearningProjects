cmake_minimum_required(VERSION 3.10)
project(HeadLightSimulation CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_NAME HeadLightSimulation)

set(PROJECT_SOURCES 
"src/HeadLightSimulation.cpp"
"src/Icommand.cpp"
"src/main.cpp")
include_directories(include)
add_executable(${EXECUTABLE_NAME} ${PROJECT_SOURCES})
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra)
