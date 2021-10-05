#include "window.hpp"

#include <stdexcept>

namespace kodah
{
  Window::Window(const char *title, const int width, const int height)
    : _width(width), _height(height)
  {
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    _window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        _width, _height,
        SDL_WINDOW_OPENGL);

    if (!_window)
    {
      throw std::runtime_error("Failed to create SDL window!");
    }

    _context = SDL_GL_CreateContext(_window);
  }

  Window::~Window()
  {
    SDL_DestroyWindow(_window);
    SDL_Quit();
  }

  int Window::width() const
  {
    return _width;
  }

  int Window::height() const
  {
    return _height;
  }

  void Window::pollEvents() const
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          onQuit();
          break;
      }
    }
  }

  void Window::swapBuffers() const
  {
    SDL_GL_SwapWindow(_window);
  }



}