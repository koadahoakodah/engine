#include "engine.hpp"

namespace kodah
{
  Engine::Engine() = default;

  Engine::~Engine() = default;

  void Engine::createWindow(const char *title, int width, int height)
  {
    _window = std::make_shared<Window>(title, width, height);
    _renderer = std::make_unique<Renderer>(_window.get());

    _window->onQuit.append([this]() { this->_shouldQuit = true; });
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
