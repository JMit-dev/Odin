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
  WindowDesc opts;
  opts.width = 800;
  opts.height = 600;

  m_window = std::make_unique<Window>("Odin", opts);

  // if you need the resize callback (optional)
  // m_window->setResizeCallback([](int w,int h){ /* rebuild projection */ });
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
