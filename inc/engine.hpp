#pragma once

#include <GL/glew.h>
#include <memory>

#include "window.hpp"

namespace kodah
{
  class Engine
  {
   public:

    Engine();
    ~Engine();

    void createWindow(const char *title, int width, int height);
    void run();

   private:

    std::unique_ptr<Window> window;
  };
}