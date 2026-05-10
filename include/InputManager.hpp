#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <GLFW/glfw3.h>
#include <map>

/**
 * @brief Singleton-style Input Manager to handle keyboard and mouse events.
 */
class InputManager {
public:
    static void init(GLFWwindow* window);

    // Keyboard
    static bool isKeyDown(int key);
    static bool isKeyPressed(int key);

    // Mouse
    static bool isMouseButtonDown(int button);
    static bool isMouseButtonPressed(int button);
    static void getMouseNDC(GLFWwindow* window, double& outX, double& outY);

private:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // Storage for states
    static std::map<int, bool> m_keys;
    static std::map<int, bool> m_keysPressed;

    static std::map<int, bool> m_mouseButtons;
    static std::map<int, bool> m_mouseButtonsPressed;
};

#endif
