#include "graphic_component.hpp"

#include "../game_object.hpp"
#include "../../renderer/renderer.hpp"
#include "../../renderer/texture.hpp"

#include <SDL3/SDL.h>

void GraphicComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();

  renderer.drawSprite(owner->m_x, owner->m_y, owner->m_currentTexture, 50.0f);
}
