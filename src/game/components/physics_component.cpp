#include "physics_component.hpp"

#include "../game_object.hpp"
#include "collidable_component.hpp"
#include "../game.hpp"

#include <SDL3/SDL.h>

void PhysicsComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();

  game.resolveCollision(owner);
}

bool PhysicsComponent::overlaps(float cx, float cy, std::shared_ptr<CollidableComponent> c) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();

  return owner->m_x < cx + c->m_volume.w &&
    owner->m_x + m_volume.w > cx &&
    owner->m_y < cy + c->m_volume.h &&
    owner->m_y + m_volume.h > cy;
}
