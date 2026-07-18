#include "graphic_component.hpp"

#include "../game_object.hpp"
#include "../../renderer/renderer.hpp"

void GraphicComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();
  // SDL_Log("graphic %f %f\n", owner->m_x, owner->m_y);

  renderer.drawSprite(owner->m_x, owner->m_y, owner->m_currentTexture, 50.0f);
}
