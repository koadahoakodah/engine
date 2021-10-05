#include "renderer.hpp"
#include "shaders.hpp"

#include <GL/glew.h>
#include <iostream>

namespace kodah
{
  namespace
  {
    void checkShaderCompileErrors(unsigned int shader)
    {
      int successful;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &successful);

      if (!successful)
      {
        int infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength];
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog);

        std::cerr << infoLog << std::endl;
        throw std::runtime_error("Failed to compile shader!");
      }
    }

    void checkProgramLinkErrors(unsigned int program)
    {
      int successful;
      glGetProgramiv(program, GL_LINK_STATUS, &successful);

      if (!successful)
      {
        int infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        char infoLog[infoLogLength];
        glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog);

        std::cerr << infoLog << std::endl;
        throw std::runtime_error("Failed to link program!");
      }

    }
  }

  Renderer::Renderer(Window *window)
    : _window(window)
  {
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
      throw std::runtime_error("Failed to initialize GLEW!");
    }

    glViewport(0, 0, _window->width(), _window->height());

    glGenBuffers(1, &_verticesVBO);

    initShaders();

  }

  Renderer::~Renderer() = default;

  void Renderer::render() const
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void Renderer::updateVertices()
  {
    glBindBuffer(GL_ARRAY_BUFFER, _verticesVBO);
    int bufferSize = static_cast<int>(_vertices.size() * sizeof(_vertices[0]));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &_vertices[0], GL_STATIC_DRAW);
  }

  void Renderer::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
  {
    _vertices.push_back(v1);
    _vertices.push_back(v2);
    _vertices.push_back(v3);
  }

  void Renderer::initShaders()
  {
    unsigned int vertexShader = createVertexShader();
    unsigned int fragmentShader = createFragmentShader();
    _shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  }

  unsigned int Renderer::createVertexShader() const
  {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader);
    return vertexShader;
  }

  unsigned int Renderer::createFragmentShader() const
  {
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader);
    return fragmentShader;
  }

  unsigned int Renderer::createShaderProgram(
      unsigned int vertexShader, unsigned int fragmentShader) const
  {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinkErrors(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
  }
}
