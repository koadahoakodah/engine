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

    // Find a vec3 in a collection of vec3's
    // If found, return the matching index; Else, return -1
    int findVec3(glm::vec3 needle, const std::vector<glm::vec3> &haystack)
    {
      for (int i = 0; i < haystack.size(); i++)
      {
        if (haystack[i] == needle)
        {
          return i;
        }
      }

      return -1;
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

    glViewport(0, 0, this->window->getWidth(), this->window->getHeight());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    initShaders();

  }

  Renderer::~Renderer()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
  }

  void Renderer::render() const
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    //glDrawArrays(GL_TRIANGLES, 0, static_cast<int>(vertices.size()));
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
  }

  void Renderer::updateVertices() const
  {
    // Bind the vertex array object
    glBindVertexArray(vao);

    // Copy data from array of vertices into vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    int bufferSize = static_cast<int>(vertices.size() * sizeof(vertices[0]));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &vertices[0], GL_STATIC_DRAW);

    // Update element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    bufferSize = static_cast<int>(indices.size() * sizeof(indices[0]));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indices.data(), GL_STATIC_DRAW);

    // Update vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Unbind the vertex array object
    glBindVertexArray(0);
  }

  void Renderer::addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3)
  {
    int i;

    if ((i = findVec3(v1, vertices)) != -1)
    {
      indices.push_back(i);
    }
    else
    {
      indices.push_back(vertices.size());
      vertices.push_back(v1);
    }

    if ((i = findVec3(v2, vertices)) != -1)
    {
      indices.push_back(i);
    }
    else
    {
      indices.push_back(vertices.size());
      vertices.push_back(v2);
    }

    if ((i = findVec3(v3, vertices)) != -1)
    {
      indices.push_back(i);
    }
    else
    {
      indices.push_back(vertices.size());
      vertices.push_back(v3);
    }

    updateVertices();

    std::cout << "indices: " << indices.size() << std::endl;
    std::cout << "vertices: " << vertices.size() << std::endl;
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
