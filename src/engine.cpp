#include "engine.hpp"

namespace kodah
{
  Engine::Engine() = default;

  Engine::~Engine() = default;

  void Engine::createWindow(const char *title, int width, int height)
  {
    _window = std::make_unique<Window>(title, width, height);
    _renderer = std::make_unique<Renderer>(_window.get());

    _window->onQuit.append([this]() { this->_shouldQuit = true; });
  }

  void Engine::initData()
  {
    _renderer->addTriangle(
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.5f, 0.0f));

    _renderer->TEMP();
  }

  void Engine::run()
  {
    while (!_shouldQuit)
    {
      _window->pollEvents();
      _renderer->render();
      _window->swapBuffers();
    }
  }
}
