#ifndef PATIENCE_TEXTURE_H 
#define PATIENCE_TEXTURE_H

#include <glad/glad.h>

struct Dimensions {
  int w;
  int h;
};

struct UV {
  float u;
  float v;
};

struct TexCoord {
  UV tl;
  UV tr;
  UV bl;
  UV br;
};

class Texture {
  GLuint m_currentTexture{};
  GLuint m_shaderProgram{};
  int m_rows{};
  int m_columns{};
  int m_width{};
  int m_height{};
  int m_texWidth{};
  int m_texHeight{};

  public:
    Texture(GLuint shaderProgram): m_shaderProgram(shaderProgram) {}
    void loadTexture(const char* path, int tx, int ty, int sw, int sh);
    TexCoord getTextureCoords(int textureIndex);
    void use();
    Dimensions getTexDimensions();
};

#endif
