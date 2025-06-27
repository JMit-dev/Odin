#ifndef APPLICATION_H
#define APPLICATION_H

#include <functional>
#include <memory>

namespace Engine {
class Window;

class Application {
public:
  using UpdateFn = std::function<void(float)>;

  static Application &instance();
  int run();

  void setUpdateCallback(UpdateFn fn) { m_update = std::move(fn); }

private:
  Application();
  ~Application() = default;

  void onUpdate(float dt);

  std::unique_ptr<Window> m_window;
  UpdateFn m_update;
  bool m_running{false};
};
} // namespace Engine

#endif
