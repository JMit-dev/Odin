#ifndef RENDER_COMMAND_H
#define RENDER_COMMAND_H

#include <glad/glad.h>

namespace Engine::Renderer {
class RenderCommand {
public:
  static void setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
  }

  static void clear(bool depth = true, bool stencil = false) {
    GLbitfield mask = GL_COLOR_BUFFER_BIT;
    if (depth)
      mask |= GL_DEPTH_BUFFER_BIT;
    if (stencil)
      mask |= GL_STENCIL_BUFFER_BIT;
    glClear(mask);
  }

  static void enableDepthTest(bool enable) {
    if (enable)
      glEnable(GL_DEPTH_TEST);
    else
      glDisable(GL_DEPTH_TEST);
  }
  static void setDepthWrite(bool enable) {
    glDepthMask(enable ? GL_TRUE : GL_FALSE);
  }

  static void setDepthFunc(GLenum func = GL_LESS) { glDepthFunc(func); }

  static void enableWireframe(bool on = true) {
    glPolygonMode(GL_FRONT_AND_BACK, on ? GL_LINE : GL_FILL);
  }

  static void enableCullFace(bool on = true, GLenum mode = GL_BACK) {
    if (on) {
      glEnable(GL_CULL_FACE);
      glCullFace(mode);
    } else {
      glDisable(GL_CULL_FACE);
    }
  }
};
} // namespace Engine::Renderer
#endif
