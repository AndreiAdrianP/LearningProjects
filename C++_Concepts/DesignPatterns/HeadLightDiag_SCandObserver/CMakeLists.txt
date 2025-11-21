cmake_minimum_required(VERSION 3.10)
project(HeadLightDiag CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_NAME HeadLightDiag)

set(HEADLIGHT_CORE_SOURCES src/HeadLightSimulation.cpp) 
set(COMMAND_CORE_SROUCES src/Icommand.cpp )

# Build external libraries
add_library(HeadLightCore STATIC ${HEADLIGHT_CORE_SOURCES})
target_include_directories(HeadLightCore PUBLIC include)
target_compile_options(HeadLightCore PRIVATE -Wall -Wextra)

add_library(CommandModule STATIC ${COMMAND_CORE_SROUCES})
target_include_directories(CommandModule PUBLIC include)
target_compile_options(CommandModule PRIVATE -Wall -Wextra)



set(MAIN_SOURCE src/main.cpp)
add_executable(${EXECUTABLE_NAME} ${MAIN_SOURCE})
target_include_directories(${EXECUTABLE_NAME} PUBLIC include)
target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${EXECUTABLE_NAME}
    PRIVATE
        HeadLightCore
        CommandModule
)
