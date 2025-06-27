#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>

namespace Engine::Renderer {
class VertexBuffer {
public:
  VertexBuffer(const void *data, unsigned size) {
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }
  ~VertexBuffer() { glDeleteBuffers(1, &m_id); }
  void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

private:
  unsigned m_id{};
};
} // namespace Engine::Renderer

#endif
