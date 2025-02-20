cmake_minimum_required(VERSION 3.10)

# Set the project name
project(false_sharing)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(false_sharing main.cpp)