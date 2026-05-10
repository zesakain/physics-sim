#include <GLFW/glfw3.h>
#include <iostream>
#include "PhysicsEngine.hpp"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. Create Window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Physics Simulation - Falling Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 3. Initialize Physics Engine (Start at height 1.0, which is top of screen in normalized coords)
    PhysicsEngine engine(1.0, 0.0, -0.5); // Using smaller gravity for visual clarity
    double lastTime = glfwGetTime();

    // 4. Main Loop
    while (!glfwWindowShouldClose(window)) {
        // Calculate delta time
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // --- Physics Step ---
        if (engine.isFalling()) {
            engine.step(deltaTime);
        }

        // --- Rendering ---
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark background

        SimulationState state = engine.getState();

        // Draw a simple square representing the object
        glPushMatrix();
        glTranslated(0.0, state.position, 0.0); // Move object to current Y position

        glBegin(GL_QUADS);
            glColor3f(0.0f, 0.8f, 1.0f); // Cyan color
            glVertex2f(-0.05f, -0.05f);
            glVertex2f( 0.05f, -0.05f);
            glVertex2f( 0.05f,  0.05f);
            glVertex2f(-0.05f,  0.05f);
        glEnd();
        glPopMatrix();

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
