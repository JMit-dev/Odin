#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include <glad/glad.h>

namespace Engine::Renderer {
class UniformBuffer {
public:
  UniformBuffer(GLsizeiptr size, GLuint bindingIndex) {
    glGenBuffers(1, &m_id);
    bind();
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingIndex, m_id);
  }
  ~UniformBuffer() { glDeleteBuffers(1, &m_id); }

  void bind() const { glBindBuffer(GL_UNIFORM_BUFFER, m_id); }

  // update whole buffer
  void setData(const void *data, GLsizeiptr size, GLintptr offset = 0) const {
    bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
  }

private:
  GLuint m_id{};
};
} // namespace Engine::Renderer
#endif
