#include "engine.hpp"

#include <iostream>

void run(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  try {
    run(argc, argv);
  }
  catch (std::runtime_error &error) {
    std::cerr << error.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void run(int argc, char *argv[]) {
  if (argc != 3) {
    throw std::runtime_error("Need 2 arguments for paths to vertex and fragment shaders!");
  }

  kodah::Engine engine{};
  engine.createWindow("New Window", 800, 600);
  engine.addShader(argv[1], argv[2]);
  engine.addTriangle(
    glm::vec3(0.5f, 0.5f, 0.0f),
    glm::vec3(0.5f, -0.5f, 0.0f),
    glm::vec3(-0.5f, 0.5f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
  );
  engine.addTriangle(
    glm::vec3(0.5f, -0.5f, 0.0f),
    glm::vec3(-0.5f, -0.5f, 0.0f),
    glm::vec3(-0.5f, 0.5f, 0.0f),
    glm::vec3(1.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 1.0f)
  );

  engine.run();
}
