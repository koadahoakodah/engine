#include "engine.hpp"

namespace kodah
{
  Engine::Engine()
  {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
  }

  Engine::~Engine()
  {
    SDL_Quit();
  }

  void Engine::createWindow(const char *title, int width, int height)
  {
    window = std::make_unique<Window>(title, width, height);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
      throw std::runtime_error("Failed to initialize GLEW!");
    }

    glViewport(0, 0, width, height);

    window->show();
  }

}
