#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "PhysicsEngine.hpp"
#include "InputManager.hpp"

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Upgraded entity structure
struct Cube {
    PhysicsEngine physics;
    float x_pos;
    bool isSelected; // Tracks if the user is controlling this cube
};

int main() {
    // 1. Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 2. Create Window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Physics Simulation - Interactive Cubes", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize our custom InputManager BEFORE the main loop
    InputManager::init(window);

    // 3. Initialize Multiple Cubes
    std::vector<Cube> cubes;
    const int NUM_CUBES = 10;

    for (int i = 0; i < NUM_CUBES; ++i) {
        float x_offset = -0.8f + (i * (1.6f / (NUM_CUBES - 1)));
        double start_y = 1.0 - (i * 0.05);

        cubes.push_back({
            PhysicsEngine(start_y, 0.0, -0.5),
            x_offset,
            false // All cubes start unselected
        });
    }

    double lastTime = glfwGetTime();
    bool mouseWasPressed = false;

    // 4. Main Loop (Only ONE loop)
    while (!glfwWindowShouldClose(window)) {
        // Calculate frame delta time
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // --- Mouse Click Detection (Raycasting) ---
                if (InputManager::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
                    double ndc_x, ndc_y;
                    InputManager::getMouseNDC(window, ndc_x, ndc_y);

                    for (auto& cube : cubes) {
                        float cube_y = static_cast<float>(cube.physics.getState().position);

                        if (ndc_x >= cube.x_pos - 0.04f && ndc_x <= cube.x_pos + 0.04f &&
                            ndc_y >= cube_y - 0.04f && ndc_y <= cube_y + 0.04f) {

                            for (auto& c : cubes) c.isSelected = false; // Deselect others
                            cube.isSelected = true; // Select this one
                            std::cout << "Cube selected at X: " << cube.x_pos << std::endl;
                            break;
                        }
                    }
                }

        // --- Update Logic ---
        for (auto& cube : cubes) {
            if (cube.isSelected) {
                // Kinematic State: Controlled by WASD
                float speed = 2.0f * static_cast<float>(deltaTime);

                // Get the current Y from the physics engine
                float current_y = static_cast<float>(cube.physics.getState().position);

                // Using our new clean API
                if (InputManager::isKeyDown(GLFW_KEY_W)) current_y += speed;
                if (InputManager::isKeyDown(GLFW_KEY_S)) current_y -= speed;
                if (InputManager::isKeyDown(GLFW_KEY_A)) cube.x_pos -= speed;
                if (InputManager::isKeyDown(GLFW_KEY_D)) cube.x_pos += speed;

                // Boundary constraints
                if (cube.x_pos < -0.95f) cube.x_pos = -0.95f;
                if (cube.x_pos >  0.95f) cube.x_pos =  0.95f;
                if (current_y < -0.95f) current_y = -0.95f;
                if (current_y >  0.95f) current_y =  0.95f;

                // Force the physics engine to update to the manual position
                cube.physics.reset(current_y);
            } else {
                // Dynamic State: Let the PhysicsEngine handle falling
                cube.physics.step(deltaTime);
            }
        }

        // --- Rendering ---
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

        for (const auto& cube : cubes) {
            SimulationState state = cube.physics.getState();

            glPushMatrix();
            glTranslated(cube.x_pos, state.position, 0.0);

            glBegin(GL_QUADS);
                if (cube.isSelected) {
                    glColor3f(0.2f, 1.0f, 0.2f); // Green
                } else if (cube.x_pos < 0) {
                    glColor3f(0.0f, 0.8f, 1.0f); // Cyan
                } else {
                    glColor3f(1.0f, 0.5f, 0.2f); // Orange
                }

                glVertex2f(-0.04f, -0.04f);
                glVertex2f( 0.04f, -0.04f);
                glVertex2f( 0.04f,  0.04f);
                glVertex2f(-0.04f,  0.04f);
            glEnd();

            glPopMatrix();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
