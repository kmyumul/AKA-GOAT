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

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add an executable target
add_executable(AKA_GOAT_App 
                src/main.cpp
                src/soccerPlayer.cpp
                src/tim.cpp)

# Link required libraries
# if(UNIX OR MINGW)
#     target_link_libraries(AKA_GOAT_App 
#         pthread 
#         ws2_32      # Winsock 2
#         wsock32     # Winsock 1
#         mswsock     # Microsoft Winsock Extensions (for AcceptEx, etc.)
#     )
# endif()

# # For Windows with MSVC
# if(MSVC)
#     target_link_libraries(AKA_GOAT_App 
#         ws2_32 
#         wsock32 
#         mswsock
#     )
# endif()

