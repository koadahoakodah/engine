#pragma once

#include <vector>
#include "glm/vec2.hpp"
#include "stb_image.h"
#include "GL/glew.h"

namespace kodah {
  class Texture {
   public:
    Texture();
   private:

    std::vector<glm::vec2> coordinates;

    void addCoordinates(glm::vec2 coords);
  };
}