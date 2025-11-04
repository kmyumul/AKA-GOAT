# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(AKA_GOAT_App CXX)

# Set C++ standard to C++17 (REQUIRED for Crow)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include Crow's header files
include_directories(${PROJECT_SOURCE_DIR}/extern/crow/include)

# Include ASIO's header files
include_directories(${PROJECT_SOURCE_DIR}/extern/asio/asio/include)

# Include JSON header files
include_directories(${PROJECT_SOURCE_DIR}/extern/json/include)

# Include CSV header files
# include_directories(${PROJECT_SOURCE_DIR}/extern/csv_parser/include)

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/csv_parser)

# Add an executable target
add_executable(AKA_GOAT_App 
                src/main.cpp
                src/soccerPlayer.cpp
                src/tim.cpp
                src/quick.cpp)

target_link_libraries(AKA_GOAT_App csv)

