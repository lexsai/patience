#ifndef PATIENCE_GAME_COMPONENTS_MAP_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_MAP_COMPONENT_HPP

#include "component.hpp"

#include <vector>
#include <string>

struct MapLayer {
  int height;
  int width;
  std::vector<int> tiles;
};

struct MapCollisionBox {
  int x;
  int y;
  int w;
  int h;
};

class MapComponent: public Component {
  public:
    MapLayer m_floorLayer{};
    MapLayer m_ceilingLayer{};

    explicit MapComponent(std::shared_ptr<GameObject>& gameObject): 
      Component{ ComponentId::Map, gameObject } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;

    void loadMap(const char* filename);
};

#endif
