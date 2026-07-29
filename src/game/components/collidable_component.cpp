#include "collidable_component.hpp"

#include "../game_object.hpp"

void CollidableComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();
}
