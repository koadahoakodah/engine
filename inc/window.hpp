#pragma once

#include <SDL.h>

namespace kodah
{
  class Window
  {
   public:

    Window(const char *title, int width, int height);
    ~Window();

    void pollEvent();

    bool shouldClose();
    void onQuit(); // make this an event; invoke when needed

   private:
    SDL_Window *window;
    SDL_GLContext context;
    SDL_Event *event;
  };
}
