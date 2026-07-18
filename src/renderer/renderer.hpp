#ifndef PATIENCE_RENDERER_H
#define PATIENCE_RENDERER_H

#include <vector>
#include <glad/glad.h>

#include "texture.hpp"

struct Vertex {
  float position[2];
  float texCoord[2];
};

class Renderer {
  int m_maxVertices{};
  std::vector<Vertex> m_vertices{};
  GLuint m_vao{};
  // TODO: create some abstraction for shaders and textures when we have more than 1 shader and texture
  GLuint m_shaderProgram{};
  Texture m_texture{ 0 };

  void addVertex(float x, float y, float u, float v);
  void loadShader(const char* vertPath, const char* fragPath);

  public:
    Renderer(int maxVertices)
      : m_maxVertices(maxVertices) {}

    void init();
    void begin();
    void end();

    void drawSprite(float x, float y, int textureIndex, float scaleFactor);
};

#endif
