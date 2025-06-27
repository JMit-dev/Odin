#ifndef SHADER_H
#define SHADER_H
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

namespace Engine::Renderer {
class Shader {
public:
  Shader(const char *vertexPath, const char *fragmentPath);
  ~Shader() { glDeleteProgram(m_id); }

  void bind() const { glUseProgram(m_id); }

  void setFloat(const std::string &name, float v) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), v);
  }

private:
  void checkCompileErrors(unsigned, const std::string &);
  unsigned m_id{};
};
} // namespace Engine::Renderer
#endif
