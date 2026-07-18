#include "game.hpp"
#include "game_object.hpp"
#include "../renderer/renderer.hpp"

// TODO: where should this go..?
GameObjectFactory gameObjectFactory{};

void Game::init() {
  std::shared_ptr<GameObject> player = gameObjectFactory.createPlayer(50.0f, 50.0f);
  m_gameObjects[player->m_id] = std::move(player);

  std::shared_ptr<GameObject> test = gameObjectFactory.createPlayer(50.0f, 200.0f);
  m_gameObjects[test->m_id] = std::move(test);
}

void Game::update(Renderer& renderer, UserCommand& userCommand) {
  renderer.begin();
    for (auto &[objId, obj]: m_gameObjects) {
      obj->update(*this, renderer, userCommand);
    }
    // for (float i = 0.0f; i < 640.0f; i += 16.0f) {
    //   renderer.drawSprite(i, 100.0f * std::sin(i + SDL_GetTicks() / 300.0f) + 160.0f, 0, 100.0f);
    // }
  renderer.end();
}
