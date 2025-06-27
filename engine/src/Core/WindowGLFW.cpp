#include <Engine/Core/Input.h>
#include <Engine/Core/Window.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {
Window::Window(const std::string &title, unsigned w, unsigned h) {
  if (!glfwInit())
    throw std::runtime_error("GLFW init failed");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_handle = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
  if (!m_handle)
    throw std::runtime_error("Window creation failed");

  glfwMakeContextCurrent(m_handle);
  glfwSetFramebufferSizeCallback(m_handle, framebufferSizeCallback);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    throw std::runtime_error("Failed to load GL");

  Input::setWindow(m_handle);
}

Window::~Window() {
  glfwDestroyWindow(m_handle);
  glfwTerminate();
}

void Window::pollEvents() { glfwPollEvents(); }
void Window::swapBuffers() { glfwSwapBuffers(m_handle); }
bool Window::shouldClose() const { return glfwWindowShouldClose(m_handle); }

void Window::framebufferSizeCallback(GLFWwindow *, int w, int h) {
  glViewport(0, 0, w, h);
}
} // namespace Engine
