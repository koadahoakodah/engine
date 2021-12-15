cmake_minimum_required(VERSION 3.20)
project(engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/engine.cpp
  ${PROJECT_SOURCE_DIR}/src/main.cpp
  ${PROJECT_SOURCE_DIR}/src/renderer.cpp
  ${PROJECT_SOURCE_DIR}/src/shader.cpp
  ${PROJECT_SOURCE_DIR}/src/texture.cpp
  ${PROJECT_SOURCE_DIR}/src/window.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/lib/fmt EXCLUDE_FROM_ALL)

target_link_libraries(${PROJECT_NAME} PUBLIC
  SDL2::SDL2 SDL2::SDL2main
  OpenGL::GL
  GLEW::GLEW
  fmt::fmt
)

# include header-only libraries
target_include_directories(${PROJECT_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/inc
  ${PROJECT_SOURCE_DIR}/lib/eventpp/include
  ${PROJECT_SOURCE_DIR}/lib/glm
  ${PROJECT_SOURCE_DIR}/lib/stb
)

