cmake_minimum_required(VERSION 3.10)
project(PhysicsSim VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define include directories so headers in include/ can be found
include_directories(include)

# Find Packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Include directories
include_directories(include)

# Gather source files
set(SOURCES
    src/main.cpp
    src/PhysicsEngine.cpp
    src/InputManager.cpp
)

# Create the executable
add_executable(PhysicsSim ${SOURCES})

# Link libraries
target_link_libraries(PhysicsSim glfw OpenGL::GL)

# Installation rules (optional for larger projects)
install(TARGETS PhysicsSim DESTINATION bin)
