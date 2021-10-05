#pragma once

#include "window.hpp"
#include "glm/vec3.hpp"

namespace kodah
{
  class Renderer
  {
   public:

    explicit Renderer(Window *window);
    ~Renderer();

    void render() const;
    void addTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

   private:

    Window *_window;
    std::vector<glm::vec3> vertices;
  };
}