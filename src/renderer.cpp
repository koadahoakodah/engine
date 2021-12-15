#include "renderer.hpp"
#include "shaders.hpp"

#include <GL/glew.h>
#include <iostream>

namespace kodah {
  namespace {
    // Find a vec3 in a collection of vec3's
    // If found, return the matching index; Else, return -1
    int findVec3(glm::vec3 needle, const std::vector<glm::vec3> &haystack) {
      for (int i = 0; i < haystack.size(); i++) {
        if (haystack[i] == needle) {
          return i;
        }
      }

      return -1;
    }
  }

  Renderer::Renderer(Window *window)
    : window(window) {
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
      throw std::runtime_error("Failed to initialize GLEW!");
    }

    glViewport(0, 0, this->window->getWidth(), this->window->getHeight());

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vboVertices);
    glGenBuffers(1, &vboColors);
    glGenBuffers(1, &ebo);

  }

  Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboColors);
    glDeleteBuffers(1, &ebo);
  }

  void Renderer::render() const {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto shader = shaders[0];

    shader.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);

    // UNIFORMS
    float timeValue = Window::getTime();
    float greenValue = sin(timeValue * 0.001f) / 2.0f + 0.5f;
    shader.setUniform("ourColor", 1.0f / greenValue * 0.5f, greenValue, 1.0f / greenValue, 1.0f);
  }

  void Renderer::addVertex(const glm::vec3 vertex, const glm::vec3 color) {
    int i = findVec3(vertex, vertices);

    if (i != -1) {
      indices.push_back(i);
    }
    else {
      indices.push_back(vertices.size());
      vertices.push_back(vertex);
      colors.push_back(color);
    }
  }

  void Renderer::updateVertices() const {
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
    glm::vec3 c1, glm::vec3 c2, glm::vec3 c3
  ) {
    addVertex(v1, c1);
    addVertex(v2, c2);
    addVertex(v3, c3);

    updateVertices();

  }

  void Renderer::addShader(const char *vertexPath, const char *fragmentPath) {
    shaders.emplace_back(vertexPath, fragmentPath);
  }

  // use this method for testing
  void Renderer::TEMP() {
  }

}
