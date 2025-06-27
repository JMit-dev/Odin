#include <Engine/Core/Input.h>

namespace Engine {
GLFWwindow *Input::s_window = nullptr;
InputMap Input::s_map = {};
Input::KeyFn Input::s_keyCb = nullptr;
Input::MouseFn Input::s_mouseCb = nullptr;

void Input::setWindow(GLFWwindow *w) {
  s_window = w;
  glfwSetKeyCallback(w, keyCallback);
  glfwSetCursorPosCallback(w, cursorCallback);
}

bool Input::isKeyPressed(int key) {
  return s_window && glfwGetKey(s_window, key) == GLFW_PRESS;
}

void Input::keyCallback(GLFWwindow *, int key, int sc, int action, int mods) {
  if (s_keyCb)
    s_keyCb(key, action);
  // Example usage of mapping:
  // if (key == s_map.keyForward && action == GLFW_PRESS) ...
}

void Input::cursorCallback(GLFWwindow *, double x, double y) {
  if (s_mouseCb)
    s_mouseCb(x, y);
}
} // namespace Engine
