#include "renderer.hpp"

#include <GL/glew.h>

namespace kodah
{
  Renderer::Renderer(Window *window)
    : _window(window)
  {
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
      throw std::runtime_error("Failed to initialize GLEW!");
    }

    glViewport(0, 0, window->width(), window->height());
  }

  Renderer::~Renderer() = default;

  void Renderer::render() const
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
}
