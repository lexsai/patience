
#ifndef PATIENCE_GAME_COMPONENTS_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_COMPONENT_HPP

#include <memory>

class Component;
class Game;
class Renderer;
struct UserCommand;
class GameObject;

// TODO: get rid of this
enum class ComponentId: unsigned int {
  Movement,
  Graphic,
  Animation,
  Physics
};

class Component {
  protected:
    std::weak_ptr<GameObject> m_ownerObject{};

    Component(ComponentId id, std::shared_ptr<GameObject>& gameObject): 
      m_ownerObject{ gameObject }, m_id{ id } {}
  public:
    ComponentId m_id{};

    virtual void update(Game& game, Renderer& renderer, UserCommand& userCommand) = 0;
};

#endif
