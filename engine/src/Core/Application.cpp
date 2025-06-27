#include <Engine/Core/Application.h>
#include <Engine/Core/Input.h>
#include <Engine/Core/Time.h>
#include <Engine/Core/Window.h>
#include <GLFW/glfw3.h>

namespace Engine {
Application &Application::instance() {
  static Application app;
  return app;
}

Application::Application() {
  m_window = std::make_unique<Window>("Odin", 800, 600);
}

int Application::run() {
  m_running = true;
  Time::init();

  while (m_running && !m_window->shouldClose()) {
    float dt = Time::frame();
    if (m_update)
      m_update(dt);

    if (Input::isKeyPressed(GLFW_KEY_ESCAPE))
      m_running = false;

    m_window->swapBuffers();
    m_window->pollEvents();
  }
  return 0;
}
} // namespace Engine
