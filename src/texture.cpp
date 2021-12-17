#include "texture.hpp"

namespace kodah {

  Texture::Texture() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    // Use nearest neighbor filtering when textures are scaled downwards
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // Use linear filtering when textures are scaled upwards
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  }

  void Texture::addCoordinates(glm::vec2 coords) {
    coordinates.emplace_back(coords);
  }

}