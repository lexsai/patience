#ifndef PATIENCE_GAME_OBJECT_H 
#define PATIENCE_GAME_OBJECT_H

#include <map>
#include <memory>
#include <vector>
#include <string>

#include "components/component.hpp"
#include "../renderer/texture.hpp"

using GameObjectId = unsigned int;

class Component;
class Game;
class Renderer;

struct UserCommand;
class GameObject {
  friend class GameObjectFactory;

  std::map<ComponentId, std::shared_ptr<Component>> m_gameObjectComponents{};

  public:
    float m_x{};
    float m_y{};
    float m_vx{};
    float m_vy{};
    TextureSpecifier m_currentTexture{};
    GameObjectId m_id{};

    GameObject(GameObjectId id, float x, float y): m_id{ id }, m_x{ x }, m_y{ y } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand);

    bool hasComponent(ComponentId);
    std::shared_ptr<Component> getComponent(ComponentId);
  private:
    void addComponent(std::shared_ptr<Component> component);
};

class GameObjectFactory {
  GameObjectId m_lastGameObjectId{};

  public:
    std::shared_ptr<GameObject> createPlayer(float x, float y);
    std::shared_ptr<GameObject> createWall(float x, float y);
    std::shared_ptr<GameObject> createMap();

    // std::shared_ptr<Component> createComponent();

  private:
    GameObjectId getNextGameObjectId() { return m_lastGameObjectId++; }
};
#endif
