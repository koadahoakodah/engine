#pragma once

#include <SDL.h>
#include "eventpp/callbacklist.h"

namespace kodah
{
  class Window
  {
   public:

    eventpp::CallbackList<void()> onQuit;

    Window(const char *title, int width, int height);
    ~Window();

    void show() const;

   private:
    SDL_Window *window;
    SDL_GLContext context;

  };
}
