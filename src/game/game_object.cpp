#include "game_object.hpp"
#include "../renderer/renderer.hpp"

#include "game.hpp"
#include "components/animation_component.hpp"
#include "components/graphic_component.hpp"
#include "components/player_component.hpp"
#include "components/physics_component.hpp"
#include "components/collidable_component.hpp"
#include "components/map_component.hpp"

#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <iostream>

std::map<std::string, std::vector<Frame>> playerAnimations {
  {"down", {{{0, 72, 16, 24}, 0.25f}, {{32, 72, 16, 24}, 0.25f}, {{0, 72, 16, 24}, 0.25f}, {{16, 72, 16, 24}, 0.25f}}},
  {"right", {{{0, 48, 16, 24}, 0.25f}, {{16, 48, 16, 24}, 0.25f}, {{0, 48, 16, 24}, 0.25f}, {{32, 48, 16, 24}, 0.25f}}},
  {"left", {{{0, 24, 16, 24}, 0.25f}, {{16, 24, 16, 24}, 0.25f}, {{0, 24, 16, 24}, 0.25f}, {{32, 24, 16, 24}, 0.25f}}},
  {"up", {{{0, 0, 16, 24}, 0.25f}, {{16, 0, 16, 24}, 0.25f}, {{0, 0, 16, 24}, 0.25f}, {{32, 0, 16, 24}, 0.25f}}},
  {"down_idle", {{{0, 72, 16, 24}, 0.25f}}},
  {"right_idle", {{{0, 48, 16, 24}, 0.25f}}},
  {"left_idle", {{{0, 24, 16, 24}, 0.25f}}},
  {"up_idle", {{{0, 0, 16, 24}, 0.25f}}},
};

std::shared_ptr<GameObject> GameObjectFactory::createPlayer(float x, float y) {
  auto player_ptr = std::shared_ptr<GameObject> {
    new GameObject{ getNextGameObjectId(), x, y }
  };
  player_ptr->addComponent(std::shared_ptr<Component>{ new PlayerComponent(player_ptr) });
  player_ptr->addComponent(std::shared_ptr<Component>{ 
    new PhysicsComponent(player_ptr, {50.0f, 75.0f}) 
  });
  player_ptr->addComponent(std::shared_ptr<Component>{ 
    new AnimationComponent(player_ptr, playerAnimations, "up")
  });
  player_ptr->addComponent(std::shared_ptr<Component>{ new GraphicComponent(player_ptr) });
  return player_ptr;
}

std::shared_ptr<GameObject> GameObjectFactory::createWall(float x, float y) {
  auto wall_ptr = std::shared_ptr<GameObject> {
    new GameObject{ getNextGameObjectId(), x, y }
  };
  wall_ptr->addComponent(std::shared_ptr<Component>{ new GraphicComponent(wall_ptr) });
  wall_ptr->addComponent(std::shared_ptr<Component>{ 
    new CollidableComponent(wall_ptr, {50.0f, 50.0f}) 
  });
  wall_ptr->m_currentTexture = {0, 72, 16, 16};
  return wall_ptr;
}

std::shared_ptr<GameObject> GameObjectFactory::createMap() {
  auto map_ptr = std::shared_ptr<GameObject> {
    new GameObject{ getNextGameObjectId(), 0, 0 }
  };
  map_ptr->addComponent(std::shared_ptr<Component>{ 
    new MapComponent(map_ptr) 
  });
  return map_ptr;
}

void GameObject::update(Game& game, Renderer& renderer, UserCommand& userCommand) { 
  m_vx = 0.0f; 
  m_vy = 0.0f;

  for (const auto &[compId, comp]: m_gameObjectComponents) {
    comp->update(game, renderer, userCommand);
  }
}

std::shared_ptr<Component> GameObject::getComponent(ComponentId componentId) {
  return m_gameObjectComponents[componentId];
}

bool GameObject::hasComponent(ComponentId componentId) {
  return m_gameObjectComponents.count(componentId) > 0;
}
void GameObject::addComponent(std::shared_ptr<Component> component) {
  m_gameObjectComponents[component->m_id] = std::move(component);
}
