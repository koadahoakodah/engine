#include "renderer.hpp"
#include "shaders.hpp"

#include <GL/glew.h>
#include <iostream>

namespace kodah
{
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

    { // Error checking
      int successful;
      char infoLog[512];
      glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &successful);
      if (!successful)
      {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        throw std::runtime_error("Failed to compile vertex shader!");
      }
    }

    return vertexShader;
  }

  unsigned int Renderer::createFragmentShader() const
  {
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    { // Error checking
      int successful;
      char infoLog[512];
      glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &successful);
      if (!successful)
      {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        throw std::runtime_error("Failed to compile fragment shader!");
      }
    }

    return fragmentShader;
  }

  unsigned int Renderer::createShaderProgram(
      unsigned int vertexShader, unsigned int fragmentShader) const
  {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    { // Error checking
      int successful;
      char infoLog[512];
      glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &successful);
      if (!successful)
      {
        glGetProgramInfoLog(_shaderProgram, 512, nullptr, infoLog);
        std::cerr << infoLog << std::endl;
        throw std::runtime_error("Failed to link shader program!");
      }
    }

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
  }
}
