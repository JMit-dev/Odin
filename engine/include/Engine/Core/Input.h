#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>

namespace Engine {
struct InputMap {
  int keyForward = GLFW_KEY_W;
  int keyBack = GLFW_KEY_S;
  int keyLeft = GLFW_KEY_A;
  int keyRight = GLFW_KEY_D;
  // ...
};

class Input {
public:
  using KeyFn =
      std::function<void(int key, int action)>; // action = GLFW_PRESS/RELEASE
  using MouseFn = std::function<void(double x, double y)>;

  static void setWindow(GLFWwindow *w);
  static void setMapping(const InputMap &map) { s_map = map; }
  static bool isKeyPressed(int key);
  static void setKeyCallback(KeyFn fn) { s_keyCb = std::move(fn); }
  static void setMouseCallback(MouseFn fn) { s_mouseCb = std::move(fn); }

private:
  static void keyCallback(GLFWwindow *, int, int, int, int);
  static void cursorCallback(GLFWwindow *, double, double);

  static GLFWwindow *s_window;
  static InputMap s_map;
  static KeyFn s_keyCb;
  static MouseFn s_mouseCb;
};
} // namespace Engine
#endif
