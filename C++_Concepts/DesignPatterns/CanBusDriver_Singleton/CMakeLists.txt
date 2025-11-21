cmake_minimum_required(VERSION 3.10)
project(CanBusDriver CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_NAME CanBusDriver)


set(CANBUS_LIB_SOURCES src/CanBusDriver_Singleton.cpp) 

add_library(CanBusDriverLib STATIC ${CANBUS_LIB_SOURCES})
target_include_directories(CanBusDriverLib PUBLIC include)
target_compile_options(CanBusDriverLib PRIVATE -Wall -Wextra -pedantic)


set(MAIN_SOURCE src/main.cpp)

add_executable(${EXECUTABLE_NAME} ${MAIN_SOURCE})
target_include_directories(${EXECUTABLE_NAME} PUBLIC include)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra -pedantic)

-
target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        CanBusDriverLib
)