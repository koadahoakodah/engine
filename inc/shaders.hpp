#pragma once

namespace kodah
{
  const char *vertexShaderSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 pos;\n"
      "void main()\n"
      "{\n"
      "  gl_Position = vec4(pos.xyz, 1.0);\n"
      "}\0";

  const char *fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 color;\n"
      "void main()\n"
      "{\n"
      "  color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
      "}\0";
}