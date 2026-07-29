#include "map_component.hpp"

#include "../game_object.hpp"
#include "../../renderer/renderer.hpp"

#include <fstream>

#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>

void MapComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();
  
  // TODO: mov e this
  constexpr int COLUMNS = 6;
  constexpr int ROWS = 6;

  for (int y = 0; y < m_floorLayer.height; y++) {
    for (int x = 0; x < m_floorLayer.width; x++) {
      int tile = m_floorLayer.tiles[y * m_ceilingLayer.width + x];
      if (tile != 0) {
        int setX = ((tile - 1) % COLUMNS) * 16;
        int setY = (ROWS - 1) * 16 - (((tile - 1) / COLUMNS) * 16); 

        renderer.drawSprite(
          x * 50.0f, (m_floorLayer.height - 1 - y) * 50.0f,
          {setX, setY, 16, 16}, 50.0f
        );
      }
    }
  }

  for (int y = 0; y < m_ceilingLayer.height; y++) {
    for (int x = 0; x < m_ceilingLayer.width; x++) {
      int tile = m_ceilingLayer.tiles[y * m_ceilingLayer.width + x];
      if (tile != 0) {
        int setX = ((tile - 1) % COLUMNS) * 16;
        int setY = (ROWS - 1) * 16 - (((tile - 1) / COLUMNS) * 16); 

        renderer.drawSprite(
          x * 50.0f, (m_ceilingLayer.height - 1 - y) * 50.0f,
          {setX, setY, 16, 16}, 50.0f
        );
      }
    }
  }
}

void MapComponent::loadMap(const char* filename) {
  std::ifstream input = std::ifstream(filename); 
  if (!input.is_open()) {
    SDL_Log("not open;\n");
  }
  SDL_Log("tryign to parse %s\n", filename);
  nlohmann::json data = nlohmann::json::parse(input);
  SDL_Log("loaded\n");

  for (auto layer: data["layers"]) {
    if (layer["name"] == "floor") {  
      for (int tile : layer["data"]) {
        m_floorLayer.tiles.push_back(tile);
      }
      m_floorLayer.height = layer["height"];
      m_floorLayer.width = layer["width"];
      SDL_Log("floor %d %d\n", m_floorLayer.height, m_floorLayer.width);
    }

    if (layer["name"] == "ceiling") {  
      SDL_Log("loaded\n");
      for (int tile : layer["data"]) {
        m_ceilingLayer.tiles.push_back(tile);
      }
      m_ceilingLayer.height = layer["height"];
      m_ceilingLayer.width = layer["width"];
      SDL_Log("ceiling %d %d\n", m_ceilingLayer.height, m_ceilingLayer.width);
    }
    // if (layer["name"] == "collisions") {  
    //   for (auto wallData : layer["objects"]) {
    //     MapCollisionBox collisionBox = {};
    //     collisionBox.w = wallData["x"];
    //     collisionBox.y = 320 - (int)wallData["y"] - (int)wallData["height"];
    //     collisionBox.endX = collisionBox.beginX + (int)wallData["width"];
    //     collisionBox.endY = collisionBox.beginY + (int)wallData["height"]; 

    //     m_collisionBoxes.push_back(collisionBox);
    //   }
    // }
  }
}
