
#ifndef PATIENCE_GAME_COMPONENTS_GRAPHIC_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_GRAPHIC_COMPONENT_HPP

#include "component.hpp"

class GameObject;

class GraphicComponent: public Component {
  public:
    explicit GraphicComponent(std::shared_ptr<GameObject>& gameObject): 
      Component{ ComponentId::Graphic, gameObject } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;
};

#endif
