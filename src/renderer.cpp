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
    glGenBuffers(1, &vboVertices);
    glGenBuffers(1, &vboColors);
    glGenBuffers(1, &ebo);

    initShaders();

  }

  Renderer::~Renderer()
  {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboColors);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
  }

  void Renderer::render() const
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);

    // TEMPORARY
    float timeValue = Window::getTime();
    float greenValue = sin(timeValue * 0.001f) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 1.0f / greenValue * 0.5f, greenValue, 1.0f / greenValue, 1.0f);
  }

  void Renderer::addVertex(const glm::vec3 vertex, const glm::vec3 color)
  {
    int i = findVec3(vertex, vertices);

    if (i != -1)
    {
      indices.push_back(i);
    }
    else
    {
      indices.push_back(vertices.size());
      vertices.push_back(vertex);
      colors.push_back(color);
    }
  }

  void Renderer::updateVertices() const
  {
    // Bind the vertex array object
    glBindVertexArray(vao);

    // Copy data from array of vertices into vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    int bufferSize = static_cast<int>(vertices.size() * sizeof(vertices[0]));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &vertices[0], GL_STATIC_DRAW);

    // Update vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // Copy data from array of colors into vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vboColors);
    bufferSize = static_cast<int>(colors.size() * sizeof(colors[0]));
    glBufferData(GL_ARRAY_BUFFER, bufferSize, &colors[0], GL_STATIC_DRAW);

    // Update color attribute pointers
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);

    // Update element buffer object
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    bufferSize = static_cast<int>(indices.size() * sizeof(indices[0]));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, indices.data(), GL_STATIC_DRAW);
    
    // Unbind the vertex array object
    glBindVertexArray(0);
  }

  void Renderer::addTriangle(
      glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
      glm::vec3 c1, glm::vec3 c2, glm::vec3 c3)
  {
    addVertex(v1, c1);
    addVertex(v2, c2);
    addVertex(v3, c3);

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
