cmake_minimum_required(VERSION 3.24)
project(Assignment6)

# Set compiler flags
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors -g")

# Define all testing related content here
enable_testing()
include(FetchContent)

# Bring in GoogleTest library v1.14.0
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

# Add in all of the header files
include_directories("./include")

# Bring together the sub-libraries
add_library(Core STATIC)
add_subdirectory(./src/objects)
add_subdirectory(./src/visitors)

# Define the source files and dependencies for the executable
set(SOURCE_FILES
    src/parser.cpp
    src/universe.cpp
)
# Make the project root directory the working directory when we run
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Build GTest automated testing suite
add_executable(testing ${SOURCE_FILES})
add_subdirectory(./tests)
add_dependencies(testing gtest Core)
target_link_libraries(testing PRIVATE gmock gtest Core nlohmann_json::nlohmann_json)