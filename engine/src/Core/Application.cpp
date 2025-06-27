#include <Engine/Core/Application.h>
#include <Engine/Core/Input.h>
#include <Engine/Core/Time.h>
#include <Engine/Core/Window.h>
#include <GLFW/glfw3.h>

namespace Engine {
Application &Application::instance(const AppDesc &desc) {
  static Application app(desc);
  return app;
}

Application::Application(const AppDesc &d) {
  if (d.headless)
    return;

  WindowDesc wopt;
  wopt.width = d.width;
  wopt.height = d.height;
  wopt.lockAspect = true;
  wopt.aspectRatio = float(d.width) / d.height;

  m_window = std::make_unique<Window>(d.title, wopt);
}

int Application::run() {
  if (!m_window)
    return 0; // headless: nothing to loop over

  m_running = true;
  Time::init();

  while (m_running && !m_window->shouldClose()) {
    float dt = Time::frame();
    if (m_update)
      m_update(dt);

    if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
      bool allowQuit = !m_onQuit || m_onQuit();
      if (allowQuit)
        m_running = false;
    }

    m_window->swapBuffers();
    m_window->pollEvents();
  }
  return 0;
}
} // namespace Engine
