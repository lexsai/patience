#ifndef PATIENCE_GAME_COMPONENTS_PLAYER_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_PLAYER_COMPONENT_HPP

#include "component.hpp"

class PlayerComponent: public Component {
  public:
    explicit PlayerComponent(std::shared_ptr<GameObject>& gameObject): 
      Component{ ComponentId::Movement, gameObject } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;
};

#endif
