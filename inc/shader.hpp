#pragma once

namespace kodah {
  class Shader {
   public:

    Shader(const char *vertexPath, const char *fragmentPath);

    ~Shader();

    void use() const;

    [[nodiscard]] unsigned int getId() const;

    void setUniform(const char *name, bool value) const;

    void setUniform(const char *name, int value) const;

    void setUniform(const char *name, float value) const;

    void setUniform(const char *name, float x, float y, float z, float w) const;

   private:

    unsigned int id;
  };
}