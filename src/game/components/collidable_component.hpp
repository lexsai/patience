#ifndef PATIENCE_GAME_COMPONENTS_COLLIDABLE_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_COLLIDABLE_COMPONENT_HPP

#include "component.hpp"

#include "volume.hpp"

class GameObject;

class CollidableComponent: public Component {
  public:
    explicit CollidableComponent(std::shared_ptr<GameObject>& gameObject, Volume volume): 
      Component{ ComponentId::Collidable, gameObject },
      m_volume{ volume } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;

    Volume m_volume{};
};

#endif
