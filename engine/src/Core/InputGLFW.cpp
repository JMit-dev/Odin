#include <Engine/Core/Input.h>
namespace Engine {
GLFWwindow *Input::s_window = nullptr;
void Input::setWindow(GLFWwindow *w) { s_window = w; }
bool Input::isKeyPressed(int key) {
  return s_window && (glfwGetKey(s_window, key) == GLFW_PRESS);
}
} // namespace Engine
