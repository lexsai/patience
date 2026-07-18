#ifndef PATIENCE_GAME_H
#define PATIENCE_GAME_H

#include <memory>
#include <map>

using GameObjectId = unsigned int;
class GameObject;
class Renderer;

struct UserCommand {
  bool forward;
  bool back;
  bool left;
  bool right;
};

class Game {
  std::map<GameObjectId, std::shared_ptr<GameObject>> m_gameObjects{};

  public:
    void init();
    void update(Renderer& renderer, UserCommand& userCommand);
};

#endif
