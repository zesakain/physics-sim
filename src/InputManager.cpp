#include "InputManager.hpp"

// Initialize static members
std::map<int, bool> InputManager::m_keys;
std::map<int, bool> InputManager::m_keysPressed;
std::map<int, bool> InputManager::m_mouseButtons;
std::map<int, bool> InputManager::m_mouseButtonsPressed;

void InputManager::init(GLFWwindow* window) {
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_keys[key] = true;
        m_keysPressed[key] = true;
    } else if (action == GLFW_RELEASE) {
        m_keys[key] = false;
    }
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        m_mouseButtons[button] = true;
        m_mouseButtonsPressed[button] = true;
    } else if (action == GLFW_RELEASE) {
        m_mouseButtons[button] = false;
    }
}

bool InputManager::isKeyDown(int key) {
    return m_keys[key];
}

bool InputManager::isKeyPressed(int key) {
    if (m_keysPressed[key]) {
        m_keysPressed[key] = false;
        return true;
    }
    return false;
}

bool InputManager::isMouseButtonDown(int button) {
    return m_mouseButtons[button];
}

bool InputManager::isMouseButtonPressed(int button) {
    if (m_mouseButtonsPressed[button]) {
        m_mouseButtonsPressed[button] = false;
        return true;
    }
    return false;
}

void InputManager::getMouseNDC(GLFWwindow* window, double& outX, double& outY) {
    double mx, my;
    int w, h;
    glfwGetCursorPos(window, &mx, &my);
    glfwGetWindowSize(window, &w, &h);

    outX = (mx / w) * 2.0 - 1.0;
    outY = 1.0 - (my / h) * 2.0;
}
