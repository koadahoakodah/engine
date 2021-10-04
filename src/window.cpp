#include "window.hpp"

#include <stdexcept>

namespace kodah
{
  Window::Window(const char *title, int width, int height)
  {
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_OPENGL);

    if (!window)
    {
      throw std::runtime_error("Failed to create SDL window!");
    }

    context = SDL_GL_CreateContext(window);
  }

  Window::~Window()
  {
    SDL_DestroyWindow(window);
  }



}