#ifndef PATIENCE_GAME_COMPONENTS_ANIMATION_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_ANIMATION_COMPONENT_HPP

#include <string>
#include <map>
#include <vector>

#include "component.hpp"

class GameObject;

struct Frame {
  int textureIndex;
  float duration;
};
using Animations = std::map<std::string, std::vector<Frame>>;

class AnimationComponent: public Component {
  float m_animationTime{};
  int m_currentFrame{};
  Animations m_animations {};
  std::string m_animationPrefix {};
  std::string m_animationSuffix {};

  public:
    AnimationComponent(
      std::shared_ptr<GameObject>& gameObject, 
      Animations animations,
      std::string initialState
    ): 
      Component{ ComponentId::Animation, gameObject }, 
      m_animations{ animations },
      m_animationPrefix{ initialState } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;
    std::vector<Frame> getFrames();
    void changeSuffix(std::string suffix);
    void changePrefix(std::string prefix);
};

#endif
