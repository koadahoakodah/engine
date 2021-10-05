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
    void initData();
    void run();


   private:

    std::shared_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;
    bool _shouldQuit = false;
  };
}