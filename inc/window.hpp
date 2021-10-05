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

    [[nodiscard]] int width() const;
    [[nodiscard]] int height() const;

    void pollEvents() const;
    void swapBuffers() const;

   private:
    SDL_Window *_window;
    SDL_GLContext _context;

    int _width;
    int _height;

  };
}
