#pragma once

#include "window.hpp"
#include "glm/vec3.hpp"

#include "shader.hpp"

#include <vector>

namespace kodah {
  class Renderer {
   public:

    explicit Renderer(Window *window);

    ~Renderer();

    void render() const;

    void addTriangle(
      glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
      glm::vec3 c1, glm::vec3 c2, glm::vec3 c3
    );

    void addShader(const char *vertexPath, const char *fragmentPath);

    void TEMP();

   private:

    Window *window;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    std::vector<unsigned int> indices;
    std::vector<Shader> shaders;

    unsigned int vao = 0;
    unsigned int vboVertices = 0;
    unsigned int vboColors = 0;
    unsigned int ebo = 0;

    void addVertex(glm::vec3 vertex, glm::vec3 color);

    void updateVertices() const;

  };
}
