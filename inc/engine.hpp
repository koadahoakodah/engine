#pragma once

#include <GL/glew.h>
#include <memory>

#include "window.hpp"
#include "renderer.hpp"

namespace kodah
{
  class Engine
  {
   public:

    Engine();
    ~Engine();

    void createWindow(const char *title, int width, int height);
    void run() const;

   private:

    std::shared_ptr<Window> window;
    std::unique_ptr<Renderer> renderer;
    bool shouldQuit = true;

    void init();
  };
}