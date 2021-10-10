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

        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, nullptr, infoLog.data());

        std::cerr << infoLog.data() << std::endl;
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

        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, nullptr, infoLog.data());

        std::cerr << infoLog.data() << std::endl;
        throw std::runtime_error("Failed to link program!");
      }

    }
  }

  Renderer::Renderer(Window *window)
    : window(window)
  {
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
      throw std::runtime_error("Failed to initialize GLEW!");
    }

    glViewport(0, 0, window->getWidth(), window->getHeight());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    initShaders();

  }

  Renderer::~Renderer() = default;

  void Renderer::render() const
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size()));
  }

  void Renderer::updateVertices() const
  {
    // Bind the vertex array object
    glBindVertexArray(vao);

    // Copy the array of vertices into a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    int bufferSize = static_cast<int>(vertices.size() * sizeof(vertices[0]));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &vertices[0], GL_STATIC_DRAW);

    // Update vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind the vertex array object
    glBindVertexArray(0);
  }

  void Renderer::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
  {
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    // update indices here (change it later for strip mesh)

    updateVertices();
  }

  void Renderer::initShaders()
  {
    unsigned int vertexShader = createVertexShader();
    unsigned int fragmentShader = createFragmentShader();
    shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  }

  unsigned int Renderer::createVertexShader()
  {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader);
    return vertexShader;
  }

  unsigned int Renderer::createFragmentShader()
  {
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader);
    return fragmentShader;
  }

  unsigned int Renderer::createShaderProgram(
      unsigned int vertexShader, unsigned int fragmentShader)
  {
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLinkErrors(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
  }

  // use this method for testing
  void Renderer::TEMP()
  {
  }
}
