#include <glad/glad.h>

#include <Engine/Core/Application.h>
#include <Engine/Core/Input.h>
#include <Engine/Renderer/RenderCommand.h>
#include <Engine/Renderer/Renderer.h>
#include <Engine/Renderer/Shader.h>
#include <Engine/Renderer/VertexArray.h>
#include <Engine/Renderer/VertexBuffer.h>

using namespace Engine;
using namespace Engine::Renderer;
using EngineRenderer = Engine::Renderer::Renderer;

int main() {
  // ── configure app -------------------------------------------------------
  AppDesc cfg;
  cfg.title = "Sandbox";
  cfg.width = 800;
  cfg.height = 600;
  // cfg.headless = true;  // flip for a non-window tool

  auto &app = Application::instance(cfg);

  // ── configure renderer (vsync off just to demo) -------------------------
  EngineRenderer::init({.vsync = false});

  // ── vertex data ---------------------------------------------------------
  float verts[] = {// pos              // color
                   0.5f, -0.5f, 0.0f, 1,    0,    0,    -0.5f, -0.5f, 0.0f,
                   0,    1,     0,    0.0f, 0.5f, 0.0f, 0,     0,     1};

  VertexArray vao;
  VertexBuffer vbo(verts, sizeof(verts));
  vao.bind();
  vao.addAttribute(0, 3, 6 * sizeof(float), 0);
  vao.addAttribute(1, 3, 6 * sizeof(float), 3 * sizeof(float));

  Shader shader("assets/shaders/triangle.vert", "assets/shaders/triangle.frag");

  // optional: quit confirmation
  app.setQuitCallback([] {
    std::puts("Esc pressed → exiting.");
    return true; // return false to cancel quit
  });

  // ── per-frame lambda -----------------------------------------------------
  app.setUpdateCallback([&](float /*dt*/) {
    EngineRenderer::beginFrame(); // profiling hook

    RenderCommand::setClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    RenderCommand::clear();

    shader.bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    EngineRenderer::endFrame();
  });

  return app.run();
}
