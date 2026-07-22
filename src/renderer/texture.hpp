#ifndef PATIENCE_TEXTURE_H 
#define PATIENCE_TEXTURE_H

#include <glad/glad.h>

struct TextureSpecifier {
  int x;
  int y;
  int w;
  int h;
};

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
  int m_width{};
  int m_height{};

  public:
    Texture(GLuint shaderProgram): m_shaderProgram(shaderProgram) {}
    void loadTexture(const char* path);
    TexCoord getTextureCoords(TextureSpecifier texture);
    void use();
    Dimensions getTexDimensions();
};

#endif
