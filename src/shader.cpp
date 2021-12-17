#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/core.h>

#include <GL/glew.h>
#include <vector>

namespace kodah {
  namespace {
    std::string readFile(const char *filepath) {
      std::ifstream file;
      file.open(filepath);
      if (file.fail()) {
        std::string message = fmt::format("Failed to open file: {}!", filepath);
        throw std::runtime_error(message);
      }

      std::stringstream stream;
      stream << file.rdbuf();
      return stream.str();
    }

    void checkShaderCompileErrors(unsigned int shader) {
      int successful;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);

      if (!successful) {
        int infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

        std::cerr << infoLog.data() << std::endl;
        throw std::runtime_error("Failed to compile shader!");
      }
    }

    void checkProgramLinkErrors(unsigned int program) {
      int successful;
      glGetProgramiv(program, GL_LINK_STATUS, &successful);

      if (!successful) {
        int infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());

        std::cerr << infoLog.data() << std::endl;
        throw std::runtime_error("Failed to link program!");
      }

    }

    unsigned int createVertexShader(const char *sourceCode) {
      unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertexShader, 1, &sourceCode, nullptr);
      glCompileShader(vertexShader);
      checkShaderCompileErrors(vertexShader);
      return vertexShader;
    }

    unsigned int createFragmentShader(const char *sourceCode) {
      unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragmentShader, 1, &sourceCode, nullptr);
      glCompileShader(fragmentShader);
      checkShaderCompileErrors(fragmentShader);
      return fragmentShader;
    }

    unsigned int createShaderProgram(unsigned int vertexShader, unsigned int fragmentShader) {
      unsigned int shaderProgram = glCreateProgram();
      glAttachShader(shaderProgram, vertexShader);
      glAttachShader(shaderProgram, fragmentShader);
      glLinkProgram(shaderProgram);
      checkProgramLinkErrors(shaderProgram);

      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);

      return shaderProgram;
    }

    int getUniformLocation(unsigned int id, const char *name) {
      int location = glGetUniformLocation(id, name);
      if (location == -1) {
        throw std::runtime_error(fmt::format("Could not find shader uniform location for name: \"{}\"", name));
      }

      return location;
    }
  }

  Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);
    unsigned int vertexShader = createVertexShader(vertexSource.c_str());
    unsigned int fragmentShader = createFragmentShader(fragmentSource.c_str());
    id = createShaderProgram(vertexShader, fragmentShader);
  }

  Shader::~Shader() {
    glDeleteProgram(id);
  }

  void Shader::use() const {
    glUseProgram(id);
  }

  unsigned int Shader::getId() const {
    return id;
  }

  void Shader::setUniform(const char *name, bool value) const {
    glUniform1i(getUniformLocation(id, name), (int) value);
  }

  void Shader::setUniform(const char *name, int value) const {
    glUniform1i(getUniformLocation(id, name), value);
  }

  void Shader::setUniform(const char *name, float value) const {
    glUniform1f(getUniformLocation(id, name), value);
  }

  void Shader::setUniform(const char *name, float x, float y, float z, float w) const {
    glUniform4f(getUniformLocation(id, name), x, y, z, w);
  }
}
