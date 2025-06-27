#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;
namespace Engine {
class Window {
public:
  Window(const std::string &title, unsigned w, unsigned h);
  ~Window();

  void pollEvents();
  void swapBuffers();
  bool shouldClose() const;

  GLFWwindow *native() const { return m_handle; }

private:
  static void framebufferSizeCallback(GLFWwindow *, int, int);
  GLFWwindow *m_handle{};
};
} // namespace Engine

#endif
