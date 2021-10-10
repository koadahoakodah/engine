#pragma once

#define SDL_MAIN_HANDLED
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

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

    void pollEvents() const;
    void swapBuffers() const;

   private:
    SDL_Window *window;
    SDL_GLContext context;

    int width;
    int height;

  };
}
