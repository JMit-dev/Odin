#ifndef APPLICATION_H
#define APPLICATION_H

#include <functional>
#include <memory>
#include <string>

namespace Engine {
struct AppDesc // configurable policy
{
  bool headless = false; // set true for CLI tools
  std::string title = "Odin";
  unsigned width = 1280;
  unsigned height = 720;
};

class Window;

class Application {
public:
  using UpdateFn = std::function<void(float)>;
  using QuitFn = std::function<bool()>; // return false to cancel

  static Application &instance(const AppDesc & = AppDesc{});

  int run();
  void setUpdateCallback(UpdateFn fn) { m_update = std::move(fn); }
  void setQuitCallback(QuitFn fn) { m_onQuit = std::move(fn); }

  Window &window() { return *m_window; }

private:
  explicit Application(const AppDesc &desc);
  ~Application() = default;

  std::unique_ptr<Window> m_window;
  UpdateFn m_update;
  QuitFn m_onQuit;
  bool m_running{false};
};
} // namespace Engine
#endif
