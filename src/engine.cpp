#include "engine.hpp"

namespace kodah
{
  Engine::Engine() = default;

  Engine::~Engine() = default;

  void Engine::createWindow(const char *title, int width, int height)
  {
    window = std::make_unique<Window>(title, width, height);
    renderer = std::make_unique<Renderer>(window.get());

    shouldQuit = false;
    window->onQuit.append([this]() { this->shouldQuit = true; });
  }

  void Engine::addShader(const char *vertexPath, const char *fragmentPath)
  {
    renderer->addShader(vertexPath, fragmentPath);
  }

  void Engine::addTriangle(
      glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
      glm::vec3 c1, glm::vec3 c2, glm::vec3 c3)
  {
    renderer->addTriangle(v1, v2, v3, c1, c2, c3);
  }


  void Engine::run() const
  {
    while (!shouldQuit)
    {
      window->pollEvents();
      renderer->render();
      window->swapBuffers();
    }
  }
}
