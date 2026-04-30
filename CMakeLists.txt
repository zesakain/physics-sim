cmake_minimum_required(VERSION 3.10)
project(PhysicsSim VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directories so headers in include/ can be found
include_directories(include)

# Gather source files
set(SOURCES 
    src/main.cpp 
    src/PhysicsEngine.cpp
)

# Create the executable
add_executable(PhysicsSim ${SOURCES})

# Installation rules (optional for larger projects)
install(TARGETS PhysicsSim DESTINATION bin)