#include "game.hpp"

#include "SDL3/SDL.h"

#include "game_object.hpp"
#include "../renderer/renderer.hpp"
#include "components/collidable_component.hpp"
#include "components/physics_component.hpp"
#include "components/map_component.hpp"

// TODO: where should this go..?
GameObjectFactory gameObjectFactory{};

void Game::init() {
  std::shared_ptr<GameObject> player = gameObjectFactory.createPlayer(50.0f, 50.0f);
  m_gameObjects[player->m_id] = std::move(player);

  std::shared_ptr<GameObject> test = gameObjectFactory.createWall(50.0f, 200.0f);
  m_gameObjects[test->m_id] = std::move(test);

  std::shared_ptr<GameObject> gameMap = gameObjectFactory.createMap();
  m_gameObjects[gameMap->m_id] = gameMap;
  m_gameMapObjectId = gameMap->m_id;

  std::shared_ptr<MapComponent> m = std::static_pointer_cast<MapComponent>(
    gameMap->getComponent(ComponentId::Map)
  );
  m->loadMap("assets/untitled.tmj");
}

void Game::update(Renderer& renderer, UserCommand& userCommand) {
  renderer.begin();
    for (auto &[objId, obj]: m_gameObjects) {
      obj->update(*this, renderer, userCommand);
    }
    // for (float i = 0.0f; i < 640.0f; i += 16.0f) {
    //   renderer.drawSprite(i, 100.0f * std::sin(i + SDL_GetTicks() / 300.0f) + 160.0f, 0, 100.0f);
    // }
    for (auto &[objId, obj]: m_gameObjects) {

    }
  renderer.end();
}

void Game::resolveCollision(std::shared_ptr<GameObject> object) {
  std::shared_ptr<PhysicsComponent> p = std::static_pointer_cast<PhysicsComponent>(
    object->getComponent(ComponentId::Physics)
  );

  float prevY = object->m_y;
  object->m_y += object->m_vy;
  for (auto &[objId, obj]: m_gameObjects) {
    if (obj->hasComponent(ComponentId::Collidable)) {
      std::shared_ptr<CollidableComponent> c = std::static_pointer_cast<CollidableComponent>(
        obj->getComponent(ComponentId::Collidable)
      );

      if (p->overlaps(obj->m_x, obj->m_y, c)) {
        object->m_y = prevY;
        break;
      }
    }
  }

  float prevX = object->m_x;
  object->m_x += object->m_vx;
  for (auto &[objId, obj]: m_gameObjects) {
    if (obj->hasComponent(ComponentId::Collidable)) {
      std::shared_ptr<CollidableComponent> c = std::static_pointer_cast<CollidableComponent>(
        obj->getComponent(ComponentId::Collidable)
      );

      if (p->overlaps(obj->m_x, obj->m_y, c)) {
        // SDL_Log("Overlapping\n");
        object->m_x = prevX;
        break;
      }
    }
  }
}
