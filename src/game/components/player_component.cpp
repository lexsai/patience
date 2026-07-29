#include "player_component.hpp"

#include "../game_object.hpp"
#include "animation_component.hpp"
#include "../game.hpp" 

#include <SDL3/SDL.h>

void PlayerComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();
  std::shared_ptr<AnimationComponent> a = std::static_pointer_cast<AnimationComponent>(
    owner->getComponent(ComponentId::Animation)
  );

  if (userCommand.forward) {
    owner->m_vy = 1.0f;
  }
  if (userCommand.back) {
    owner->m_vy = -1.0f;
  }
  if (userCommand.left) {
    owner->m_vx = -1.0f;
  }
  if (userCommand.right) {
    owner->m_vx = 1.0f;
  }

  if (owner->m_vx > 0) {
    a->changePrefix("right");
  }
  else if (owner ->m_vx < 0) {
    a->changePrefix("left");
  } 
  else if (owner->m_vy > 0) {
    a->changePrefix("up");
  }
  else if (owner->m_vy < 0) {
    a->changePrefix("down");
  }

  if (!(userCommand.forward || userCommand.back || userCommand.left || userCommand.right)) {
    a->changeSuffix("_idle");
  } else {
    a->changeSuffix("");
  }
}
