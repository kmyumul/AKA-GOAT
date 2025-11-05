# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(AKA_GOAT_App CXX)

# Set C++ standard to C++17 (REQUIRED for Crow)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/extern/csv_parser)
add_subdirectory(${PROJECT_SOURCE_DIR}/extern/terminal)

set(CPR_USE_SYSTEM_CURL ON CACHE BOOL "Use system libcurl" FORCE)
set(CPR_USE_SYSTEM_SSL  ON CACHE BOOL "Use system SSL"  FORCE)
set(CPR_USE_SYSTEM_ZLIB ON CACHE BOOL "Use system zlib" FORCE)

include(FetchContent)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.10.5
)

FetchContent_MakeAvailable(cpr)

# Add an executable target
add_executable(AKA_GOAT_App 
                src/main.cpp
                src/soccerPlayer.cpp
                src/tim.cpp
                src/quick.cpp
                src/parse_csv.cpp
                src/aka_goat.cpp)

target_include_directories(AKA_GOAT_App PRIVATE
    ${PROJECT_SOURCE_DIR}/extern/crow/include
    ${PROJECT_SOURCE_DIR}/extern/asio/asio/include
    ${PROJECT_SOURCE_DIR}/extern/json/include
    ${PROJECT_SOURCE_DIR}/extern/terminal/include
    ${PROJECT_SOURCE_DIR}/include
)

# target_link_libraries(AKA_GOAT_App csv osmanip::osmanip)
target_link_libraries(AKA_GOAT_App PRIVATE
    csv
    osmanip::osmanip
    cpr::cpr
    ${OpenCV_LIBS}
)

# Copy CPR DLL to executable folder after build
add_custom_command(TARGET AKA_GOAT_App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:cpr::cpr>
        $<TARGET_FILE_DIR:AKA_GOAT_App>
)





