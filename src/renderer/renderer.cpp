#include "renderer.hpp"
#include "texture.hpp"

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stddef.h>

namespace {
  std::string readFile(const char* path) {
    std::ifstream input = std::ifstream(path);
    if (!input.is_open()) {
      SDL_Log("could not open shader file: '%s'\n", path);
      exit(EXIT_FAILURE);
    }
    
    std::stringstream stream;
    stream << input.rdbuf();
    input.close();
    return stream.str();
  }
}

void Renderer::init() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    SDL_Log("failed to load GL functions\n");
  }
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glViewport(0, 0, 640, 480);

  glGenVertexArrays(1, &m_vao);

  GLuint VBO;
  glGenBuffers(1, &VBO);  

  glBindVertexArray(m_vao);
  loadShader("assets/shaders/vert.glsl", "assets/shaders/frag.glsl");

  m_texture = Texture{ m_shaderProgram };
  m_texture.loadTexture("assets/teto.png");

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, m_maxVertices * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoord));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
}

void Renderer::begin() {
  glClearColor(0.5f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::end() {
  glUseProgram(m_shaderProgram);

  m_texture.use();

  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
  glm::mat4 mvp = projection * view;
  GLint loc = glGetUniformLocation(m_shaderProgram, "mvp");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mvp));

  glBindVertexArray(m_vao);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(m_vertices[0]), m_vertices.data());
  glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(m_vertices.size()));
  m_vertices.clear();
}

void Renderer::drawSprite(float x, float y, TextureSpecifier t, float width) {
  float x1 = x; 
  float x2 = x + width;
  float y1 = y;
  float y2 = y + width * (t.h / static_cast<float>(t.w));

  TexCoord texCoord = m_texture.getTextureCoords({ t.x, t.y, t.w, t.h });

  addVertex(x, y, texCoord.bl.u, texCoord.bl.v);
  addVertex(x2, y2, texCoord.tr.u, texCoord.tr.v);
  addVertex(x, y2, texCoord.tl.u, texCoord.tl.v);

  addVertex(x, y, texCoord.bl.u, texCoord.bl.v);
  addVertex(x2, y, texCoord.br.u, texCoord.br.v);
  addVertex(x2, y2, texCoord.tr.u, texCoord.tr.v);
}

void Renderer::addVertex(float x, float y, float u, float v) {
  if (m_vertices.size() == m_maxVertices) {
    end();
  }
  m_vertices.push_back(Vertex {x, y, u, v});
}

void Renderer::loadShader(const char* vertPath, const char* fragPath) {
  GLint success;
  char infoLog[512];

  GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
  std::string vertString = readFile(vertPath);
  const char *vertSource = vertString.c_str();
  glShaderSource(vertShader, 1, &vertSource, nullptr);
  glCompileShader(vertShader);
  glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertShader, 512, nullptr, infoLog);
    SDL_Log("vert shader error: %s", infoLog);
  }

  GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
  std::string fragString = readFile(fragPath);
  const char *fragSource = fragString.c_str();
  glShaderSource(fragShader, 1, &fragSource, nullptr);
  glCompileShader(fragShader);
  glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
    SDL_Log("frag shader error: %s", infoLog);
  }

  m_shaderProgram = glCreateProgram();
  glAttachShader(m_shaderProgram, fragShader);
  glAttachShader(m_shaderProgram, vertShader);
  glLinkProgram(m_shaderProgram);
  glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(m_shaderProgram, 512, nullptr, infoLog);
    SDL_Log("m_shaderProgram link error: %s", infoLog);
  }

  glDeleteShader(vertShader);
  glDeleteShader(fragShader);
}
