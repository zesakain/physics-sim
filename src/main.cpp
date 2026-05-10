#include <GLFW/glfw3.h>
#include <iostream>
#include "PhysicsEngine.hpp"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

/**
 * 1. Callback function must be defined OUTSIDE of main.
 * This is triggered by GLFW events.
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Get the physics engine instance from the window's user pointer
    PhysicsEngine* engine = static_cast<PhysicsEngine*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        std::cout << "Space pressed: Applying Jump/Reset!" << std::endl;
        if (engine) {
            // Logic: Reset to top of screen with upward velocity
            engine->reset(1.0);
        }
    }
}

int main() {
    // 2. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 3. Create Window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Physics Simulation - Falling Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 4. Setup Physics Engine
    PhysicsEngine engine(1.0, 0.0, -0.8); // Slightly stronger gravity

    /**
     * 5. State Management Bridge:
     * We attach our 'engine' instance to the GLFW window.
     * This allows the callback (which is global) to access local main data.
     */
    glfwSetWindowUserPointer(window, &engine);
    glfwSetKeyCallback(window, key_callback);

    double lastTime = glfwGetTime();

    // 6. Main Loop
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
        glClearColor(0.1f, 0.11f, 0.12f, 1.0f); // Professional dark theme

        SimulationState state = engine.getState();

        // Draw the object
        glPushMatrix();
        glTranslated(0.0, state.position, 0.0);

        glBegin(GL_QUADS);
            glColor3f(0.0f, 0.7f, 1.0f); // Material Blue
            glVertex2f(-0.06f, -0.06f);
            glVertex2f( 0.06f, -0.06f);
            glVertex2f( 0.06f,  0.06f);
            glVertex2f(-0.06f,  0.06f);
        glEnd();
        glPopMatrix();

        // Draw ground line
        glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(-1.0f, -0.91f);
            glVertex2f( 1.0f, -0.91f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
