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

    void updateVertices();
    void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

   private:

    Window *_window;
    std::vector<glm::vec3> _vertices;

    unsigned int _verticesVBO = 0;
    unsigned int _shaderProgram = 0;

    void initShaders();
    [[nodiscard]] unsigned int createVertexShader() const;
    [[nodiscard]] unsigned int createFragmentShader() const;
    [[nodiscard]] unsigned int createShaderProgram(
        unsigned int vertexShader, unsigned int fragmentShader) const;

  };
}