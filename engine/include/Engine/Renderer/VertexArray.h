#ifndef VERTEX_ARRAY_BUFFER
#define VERTEX_ARRAY_BUFFER

#include <glad/glad.h>

#include <Engine/Renderer/IndexBuffer.h>

namespace Engine::Renderer {
class VertexArray {
public:
  VertexArray() { glGenVertexArrays(1, &m_id); }
  ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

  void bind() const { glBindVertexArray(m_id); }

  void addAttribute(unsigned index, int count, unsigned stride, size_t offset) {
    bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride,
                          reinterpret_cast<void *>(offset));
  }

private:
  unsigned m_id{};
  IndexBuffer *m_ibo{nullptr};
};
} // namespace Engine::Renderer

#endif
