#include "physics_component.hpp"

#include "../game_object.hpp"

void PhysicsComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();

  owner->m_x += owner->m_vx;
  owner->m_y += owner->m_vy;
}
