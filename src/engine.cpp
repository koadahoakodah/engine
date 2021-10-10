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

    init();
  }

  void Engine::init()
  {
    renderer->addTriangle(
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f));

    renderer->TEMP();
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
