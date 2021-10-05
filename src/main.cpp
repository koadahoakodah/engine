#include "engine.hpp"

#include <iostream>

int main()
{
  try
  {
    kodah::Engine engine{};
    engine.createWindow("New Window", 800, 600);
    engine.showWindow();
  }
  catch (std::runtime_error &error)
  {
    std::cerr << error.what() << std::endl;
  }
  return 0;
}
