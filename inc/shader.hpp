#pragma once

namespace kodah
{
  class Shader
  {
   public:

    Shader(const char *vertexPath, const char *fragmentPath);

    void use();

    unsigned int getId();

    void setUniform(const char *name, bool value) const;
    void setUniform(const char *name, int value) const;
    void setUniform(const char *name, float value) const;

   private:

    unsigned int id;
  };
}