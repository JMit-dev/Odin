#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>

namespace Engine::Renderer {
class IndexBuffer {
public:
  IndexBuffer(const void *data, unsigned count, GLenum type = GL_UNSIGNED_INT)
      : m_count(count), m_type(type) {
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * bytesPerIndex(), data,
                 GL_STATIC_DRAW);
  }
  ~IndexBuffer() { glDeleteBuffers(1, &m_id); }

  void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id); }
  void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

  unsigned count() const { return m_count; }
  GLenum type() const { return m_type; }

private:
  GLuint m_id{};
  unsigned m_count{};
  GLenum m_type;

  constexpr unsigned bytesPerIndex() const {
    return (m_type == GL_UNSIGNED_BYTE ? 1
                                       : (m_type == GL_UNSIGNED_SHORT ? 2 : 4));
  }
};
} // namespace Engine::Renderer
#endif
