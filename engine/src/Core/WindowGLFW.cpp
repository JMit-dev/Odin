#include <glad/glad.h>

#include <Engine/Core/Input.h>
#include <Engine/Core/Window.h>

#include <GLFW/glfw3.h>
#include <iostream>

namespace Engine {
Window::Window(const std::string &title, const WindowDesc &d) : m_desc(d) {
  if (!glfwInit())
    throw std::runtime_error("GLFW init failed");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  m_handle =
      glfwCreateWindow(d.width, d.height, title.c_str(), nullptr, nullptr);
  if (!m_handle)
    throw std::runtime_error("Window creation failed");

  glfwMakeContextCurrent(m_handle);
  glfwSetWindowUserPointer(m_handle, this);
  glfwSetFramebufferSizeCallback(m_handle, framebufferSizeCallback);

  if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    throw std::runtime_error("Failed to load GL");

  // initial viewport
  int fbW, fbH;
  glfwGetFramebufferSize(m_handle, &fbW, &fbH);
  applyViewport(fbW, fbH);

  Input::setWindow(m_handle);
}

Window::~Window() {
  glfwDestroyWindow(m_handle);
  glfwTerminate();
}

void Window::pollEvents() { glfwPollEvents(); }
void Window::swapBuffers() { glfwSwapBuffers(m_handle); }
bool Window::shouldClose() const { return glfwWindowShouldClose(m_handle); }

void Window::framebufferSizeCallback(GLFWwindow *win, int fbW, int fbH) {
  auto *self = static_cast<Window *>(glfwGetWindowUserPointer(win));
  if (self) {
    self->applyViewport(fbW, fbH);
    if (self->m_onResize)
      self->m_onResize(fbW, fbH);
  }
}

void Window::applyViewport(int fbW, int fbH) {
  if (!m_desc.lockAspect) { // free-resizing
    glViewport(0, 0, fbW, fbH);
    return;
  }

  float target = m_desc.aspectRatio;
  float winAsp = float(fbW) / fbH;

  int vpX = 0, vpY = 0, vpW = fbW, vpH = fbH;

  if (winAsp > target) { // pillar-box
    vpW = int(fbH * target);
    vpX = (fbW - vpW) / 2;
  } else if (winAsp < target) { // letter-box
    vpH = int(fbW / target);
    vpY = (fbH - vpH) / 2;
  }
  glViewport(vpX, vpY, vpW, vpH);
}
} // namespace Engine
