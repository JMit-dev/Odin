#include <Engine/Renderer/Shader.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace Engine::Renderer {
Shader::Shader(const char *v, const char *f, const char *g)
    : m_vertPath(v), m_fragPath(f), m_geomPath(g ? g : "") {
  reload();
}
Shader::~Shader() { glDeleteProgram(m_id); }

void Shader::reload() {
  // read sources
  std::string vertSrc = readFile(m_vertPath.c_str());
  std::string fragSrc = readFile(m_fragPath.c_str());
  std::string geomSrc = m_geomPath.empty() ? "" : readFile(m_geomPath.c_str());

  const char *vSrc = vertSrc.c_str();
  const char *fSrc = fragSrc.c_str();
  const char *gSrc = geomSrc.c_str();

  // compile stages
  GLuint vert = compileStage(vSrc, GL_VERTEX_SHADER);
  GLuint frag = compileStage(fSrc, GL_FRAGMENT_SHADER);
  GLuint geom = 0;
  if (!geomSrc.empty())
    geom = compileStage(gSrc, GL_GEOMETRY_SHADER);

  // link
  if (m_id)
    glDeleteProgram(m_id);
  linkProgram(vert, frag, geom);

  glDeleteShader(vert);
  glDeleteShader(frag);
  if (geom)
    glDeleteShader(geom);

  m_locationCache.clear();
}

void Shader::setBool(const std::string &n, bool v) const {
  glUniform1i(getLocation(n), (int)v);
}
void Shader::setInt(const std::string &n, int v) const {
  glUniform1i(getLocation(n), v);
}
void Shader::setFloat(const std::string &n, float v) const {
  glUniform1f(getLocation(n), v);
}

void Shader::setVec2(const std::string &n, const glm::vec2 &v) const {
  glUniform2fv(getLocation(n), 1, &v[0]);
}

void Shader::setVec3(const std::string &n, const glm::vec3 &v) const {
  glUniform3fv(getLocation(n), 1, &v[0]);
}

void Shader::setVec4(const std::string &n, const glm::vec4 &v) const {
  glUniform4fv(getLocation(n), 1, &v[0]);
}

void Shader::setMat4(const std::string &n, const glm::mat4 &v, bool t) const {
  glUniformMatrix4fv(getLocation(n), 1, t ? GL_TRUE : GL_FALSE, &v[0][0]);
}

std::string Shader::readFile(const char *path) {
  std::ifstream file(path);
  if (!file)
    throw std::runtime_error(std::string("Shader file missing: ") + path);
  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

GLuint Shader::compileStage(const char *src, GLenum type) const {
  GLuint id = glCreateShader(type);
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);
  checkErrors(id, type == GL_VERTEX_SHADER     ? "VERTEX"
                  : type == GL_FRAGMENT_SHADER ? "FRAGMENT"
                                               : "GEOMETRY");
  return id;
}

void Shader::linkProgram(GLuint vert, GLuint frag, GLuint geom) {
  m_id = glCreateProgram();
  glAttachShader(m_id, vert);
  glAttachShader(m_id, frag);
  if (geom)
    glAttachShader(m_id, geom);
  glLinkProgram(m_id);
  checkErrors(m_id, "PROGRAM");
}

void Shader::checkErrors(GLuint id, const std::string &type) {
  GLint ok;
  if (type == "PROGRAM") {
    glGetProgramiv(id, GL_LINK_STATUS, &ok);
    if (!ok) {
      char log[1024];
      glGetProgramInfoLog(id, 1024, nullptr, log);
      std::cerr << "PROGRAM LINK ERROR:\n" << log << '\n';
    }
  } else {
    glGetShaderiv(id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
      char log[1024];
      glGetShaderInfoLog(id, 1024, nullptr, log);
      std::cerr << type << " COMPILE ERROR:\n" << log << '\n';
    }
  }
}

GLint Shader::getLocation(const std::string &name) const {
  auto it = m_locationCache.find(name);
  if (it != m_locationCache.end())
    return it->second;

  GLint loc = glGetUniformLocation(m_id, name.c_str());
  m_locationCache.emplace(name, loc);
  return loc;
}
} // namespace Engine::Renderer
