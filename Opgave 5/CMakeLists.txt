cmake_minimum_required(VERSION 3.10)
project("Opgave5") # Ensure the project name is a single string (no spaces without quotes)

# Fetch Unity if you are using it for unit testing
include(FetchContent)
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(unity)

# Include directories
include_directories(${unity_SOURCE_DIR}/src)
include_directories(include) # assuming your header files are in the 'include' directory

# Specify the source files for your project
file(GLOB SOURCES "src/*.c")

# Add the executable for the project
add_executable(Opgave5 ${SOURCES})

# Define the test executable
add_executable(test_adc test/adc.cTest)
target_link_libraries(test_adc unity)

# Optionally, set the C standard explicitly
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
