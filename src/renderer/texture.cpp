#include "texture.hpp"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include "stb_image.h"

void Texture::loadTexture(const char* path, int tx, int ty, int sw, int sh) {
  GLuint texture;
  glGenTextures(1, &texture);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height, nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
  if (data)
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    SDL_Log("failed to load texture '%s'\n", path);
  }
  stbi_image_free(data);

  m_currentTexture = texture;
  m_rows = tx;
  m_columns = ty;
  m_width = width;
  m_height = height;
  m_texWidth = sw;
  m_texHeight = sh;
}

TexCoord Texture::getTextureCoords(int textureIndex) {
  int x = textureIndex % m_columns;
  int y = (m_rows - 1) - textureIndex / m_columns;

  float tileWidth = m_texWidth / static_cast<float>(m_width);
  float tileHeight = m_texHeight / static_cast<float>(m_height);

  float u_min = x * tileWidth;
  float u_max = (x + 1) * tileWidth;
  float v_min = y * tileHeight;
  float v_max = (y + 1) * tileHeight;

  return {
    { u_min, v_max },
    { u_max, v_max },
    { u_min, v_min },
    { u_max, v_min },
  };
}

void Texture::use() {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, m_currentTexture);
  glUniform1i(glGetUniformLocation(m_shaderProgram, "uTexture"), 0);
}

Dimensions Texture::getTexDimensions() {
  return { m_texWidth, m_texHeight };
}
