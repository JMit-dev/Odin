#include <glad/glad.h>

#include <Engine/Renderer/Renderer.h>
#include <GLFW/glfw3.h>

namespace Engine::Renderer {
Renderer::Hook Renderer::s_onBegin = nullptr;
Renderer::Hook Renderer::s_onEnd = nullptr;

void Renderer::init(const RendererDesc &d) {
  glfwSwapInterval(d.vsync ? 1 : 0);
  if (d.enableDepth)
    glEnable(GL_DEPTH_TEST);
}

void Renderer::beginFrame() {
  if (s_onBegin)
    s_onBegin();
}

void Renderer::endFrame() {
  if (s_onEnd)
    s_onEnd();
}
} // namespace Engine::Renderer
