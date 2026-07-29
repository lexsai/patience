#ifndef PATIENCE_GAME_COMPONENTS_PHYSICS_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_PHYSICS_COMPONENT_HPP

#include "component.hpp"

#include "volume.hpp"

class CollidableComponent;
class GameObject;

class PhysicsComponent: public Component {
  Volume m_volume{};

  public:
    explicit PhysicsComponent(std::shared_ptr<GameObject>& gameObject, Volume volume): 
      Component{ ComponentId::Physics, gameObject },
      m_volume{ volume } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;

    bool overlaps(float x, float y, std::shared_ptr<CollidableComponent> c);
};

#endif
