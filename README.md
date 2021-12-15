# graphics engine

**Currently in development**

Dependencies:
- [SDL2](https://www.libsdl.org/download-2.0.php) (for creating a window)
- [GLEW](http://glew.sourceforge.net/) (for OpenGL)
- [CMake](https://cmake.org/download/) (for building)

To download git submodules:
- ```cd``` into the root directory of this project
- ```git submodule init``` to initialize git submodules
- ```git submodule update``` to download git submodules

To build and run project:
- ```cd``` into the root directory of this project
- ```cmake -S . -B build``` to initialize cmake
- ```cmake --build build``` to build project
- ```./run.sh``` to run project