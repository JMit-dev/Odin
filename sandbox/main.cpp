#include <Engine/Core/Application.h>
#include <Engine/Renderer/RenderCommand.h>
#include <Engine/Renderer/Shader.h>
#include <Engine/Renderer/VertexArray.h>
#include <Engine/Renderer/VertexBuffer.h>

using namespace Engine;
using namespace Engine::Renderer;

int main() {
  auto &app = Application::instance();

  // ── vertex data ─────────────────────────────────────────────
  float vertices[] = {// pos           // color
                      0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.0f,
                      0.0f, 1.0f,  0.0f, 0.0f, 0.5f, 0.0f, 0.0f,  0.0f,  1.0f};

  VertexArray vao;
  vao.bind();
  VertexBuffer vbo(vertices, sizeof(vertices));
  vao.addAttribute(0, 3, 6 * sizeof(float), 0);
  vao.addAttribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));

  // ── shaders (assets/shaders/simple.vert/frag) ───────────────
  Shader shader("assets/shaders/simple.vert", "assets/shaders/simple.frag");

  // ── register per-frame lambda ───────────────────────────────
  app.setUpdateCallback([&](float /*dt*/) {
    RenderCommand::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    RenderCommand::clear();

    shader.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
  });

  return app.run();
