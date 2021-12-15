#pragma once

#include <memory>

#include "window.hpp"
#include "renderer.hpp"

namespace kodah {
  class Engine {
   public:

    Engine();

    ~Engine();

    void createWindow(const char *title, int width, int height);

    void addShader(const char *vertexPath, const char *fragmentPath);

    void addTriangle(
      glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
      glm::vec3 c1, glm::vec3 c2, glm::vec3 c3
    );

    void run() const;

   private:

    std::shared_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    bool shouldQuit = true;
  };
}