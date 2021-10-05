#pragma once

#include "window.hpp"

namespace kodah
{
  class Renderer
  {
   public:

    explicit Renderer(Window *window);
    ~Renderer();

    void render() const;
    //void addTriangle(

   private:

    Window *_window;
  };
}