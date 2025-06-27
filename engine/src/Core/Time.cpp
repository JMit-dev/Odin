#include <Engine/Core/Time.h>
#include <GLFW/glfw3.h>

namespace Engine {
double Time::s_last = 0.0;
double Time::s_now = 0.0;

void Time::init() { s_last = s_now = glfwGetTime(); }

float Time::frame() {
  s_now = glfwGetTime();
  float dt = static_cast<float>(s_now - s_last);
  s_last = s_now;
  return dt;
}

float Time::total() { return static_cast<float>(glfwGetTime()); }
} // namespace Engine
