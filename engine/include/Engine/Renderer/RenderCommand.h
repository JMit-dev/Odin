#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include <glad/glad.h>

namespace Engine::Renderer {
class RenderCommand {
public:
  static void setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
  }
  static void clear() { glClear(GL_COLOR_BUFFER_BIT); }
};
} // namespace Engine::Renderer

#endif
