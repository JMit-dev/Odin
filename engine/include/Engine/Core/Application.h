#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>
namespace Engine {
class Window;

class Application {
public:
  static Application &instance();
  int run();

private:
  Application();
  ~Application() = default;

  void onUpdate(float dt);

  std::unique_ptr<Window> m_window;
  bool m_running{false};
};
} // namespace Engine

#endif
