#pragma once
#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <unordered_map>

namespace Engine::Renderer {
class Shader {
public:
  // supply geometryPath == nullptr if not needed
  Shader(const char *vertexPath, const char *fragmentPath,
         const char *geometryPath = nullptr);

  ~Shader();

  void bind() const { glUseProgram(m_id); }
  static void unbind() { glUseProgram(0); }

  void reload(); // re-read files and recompile

  void setBool(const std::string &name, bool v) const;
  void setInt(const std::string &name, int v) const;
  void setFloat(const std::string &name, float v) const;

  void setVec2(const std::string &n, const glm::vec2 &v) const;
  void setVec3(const std::string &n, const glm::vec3 &v) const;
  void setVec4(const std::string &n, const glm::vec4 &v) const;
  void setMat4(const std::string &n, const glm::mat4 &v,
               bool transpose = false) const;

private:
  // file paths kept for hot-reload
  std::string m_vertPath, m_fragPath, m_geomPath;

  mutable std::unordered_map<std::string, GLint> m_locationCache;
  GLuint m_id{};

  GLuint compileStage(const char *src, GLenum type) const;
  GLint getLocation(const std::string &name) const;
  void linkProgram(GLuint vert, GLuint frag, GLuint geom);
  static std::string readFile(const char *path);
  static void checkErrors(GLuint id, const std::string &type);
};
} // namespace Engine::Renderer
