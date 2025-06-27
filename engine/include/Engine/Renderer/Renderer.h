#ifndef RENDERER_H
#define RENDERER_H

#include <functional>

namespace Engine::Renderer {
struct RendererDesc {
  bool vsync = true;
  bool enableDepth = true;
};

class Renderer {
public:
  using Hook = std::function<void()>;

  static void init(const RendererDesc & = RendererDesc{});
  static void beginFrame();
  static void endFrame();

  static void setBeginHook(Hook h) { s_onBegin = std::move(h); }
  static void setEndHook(Hook h) { s_onEnd = std::move(h); }

private:
  static Hook s_onBegin;
  static Hook s_onEnd;
};
} // namespace Engine::Renderer
#endif
