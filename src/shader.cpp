#include "shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <fmt/core.h>

namespace kodah
{
  namespace
  {
    std::string readFile(const char *filepath)
    {
      std::ifstream file;
      file.open(filepath);
      if (file.fail())
      {
        std::string message = fmt::format("Failed to open file: {}!", filepath);
        throw std::runtime_error(message);
      }

      std::stringstream stream;
      stream << file.rdbuf();
      return stream.str();
    }

    void compileShader(const char *sourceCode)
    {

    }
  }

  Shader::Shader(const char *vertexPath, const char *fragmentPath)
  {
    std::string vertexCode = readFile(vertexPath);
    std::cout << vertexCode << std::endl;
    std::cout << vertexCode.length() << std::endl;
    //const char *fragmentCode = readFile(fragmentPath);


    id = -1;
  }

  void Shader::use()
  {

  }

  unsigned int Shader::getId()
  {
    return id;
  }

  void Shader::setUniform(const char *name, bool value) const
  {

  }

  void Shader::setUniform(const char *name, int value) const
  {

  }

  void Shader::setUniform(const char *name, float value) const
  {

  }

}
