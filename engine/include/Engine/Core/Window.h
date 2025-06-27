#ifndef WINDOW_H
#define WINDOW_H

#include <functional>
#include <string>

struct GLFWwindow;

namespace Engine {
struct WindowDesc {
  unsigned width = 1280;
  unsigned height = 720;
  bool lockAspect = true; // enable pillar/letter boxing
  float aspectRatio = 16.0f / 9.0f;
};

class Window {
public:
  using ResizeFn = std::function<void(int /*fbW*/, int /*fbH*/)>;

  explicit Window(const std::string &title,
                  const WindowDesc &desc = WindowDesc{});
  ~Window();

  void pollEvents();
  void swapBuffers();
  bool shouldClose() const;

  void setResizeCallback(ResizeFn cb) { m_onResize = std::move(cb); }
  GLFWwindow *native() const { return m_handle; }

private:
  static void framebufferSizeCallback(GLFWwindow *, int, int);
  void applyViewport(int fbW, int fbH);

  GLFWwindow *m_handle{};
  WindowDesc m_desc;
  ResizeFn m_onResize;
};
} // namespace Engine
#endif
