#pragma once

#include "window.hpp"
#include "glm/vec3.hpp"

#include <vector>

namespace kodah
{
  class Renderer
  {
   public:

    explicit Renderer(Window *window);
    ~Renderer();

    void render() const;

    void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    void TEMP();

   private:

    Window *window;
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

    unsigned int shaderProgram = 0;

    void initShaders();
    [[nodiscard]] static unsigned int createVertexShader();
    [[nodiscard]] static unsigned int createFragmentShader();
    [[nodiscard]] static unsigned int createShaderProgram(
        unsigned int vertexShader, unsigned int fragmentShader);

    void addVertex(glm::vec3);
    void updateVertices() const;

  };
}