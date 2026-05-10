## PhysicsSim
A 2D interactive physics simulation built with C++ and OpenGL.

## Features
Semi-implicit Euler integration for stable physics.

Ground collision and energy loss (bounciness).

Multiple independent entities.

Mouse raycasting for object selection.

Kinematic state control (WASD) via custom InputManager.

## Dependencies
'''bash
sudo pacman -Syu cmake gcc base-devel glfw-x11 mesa glu

## Build
```bash
mkdir build && cd build
cmake ..
make
./PhysicsSim
