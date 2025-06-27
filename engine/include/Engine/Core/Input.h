#ifndef INPUT_H
#define INPUT_H
#include <GLFW/glfw3.h>

namespace Engine {
class Input {
public:
  static void setWindow(GLFWwindow *w);
  static bool isKeyPressed(int key);

private:
  static GLFWwindow *s_window;
};
} // namespace Engine

#endif
