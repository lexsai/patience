#ifndef PATIENCE_GAME_COMPONENTS_PHYSICS_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_PHYSICS_COMPONENT_HPP

#include "component.hpp"

class GameObject;

class PhysicsComponent: public Component {
  public:
    explicit PhysicsComponent(std::shared_ptr<GameObject>& gameObject): 
      Component{ ComponentId::Physics, gameObject } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;
};

#endif
