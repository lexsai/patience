#include "animation_component.hpp"

#include <SDL3/SDL.h>

#include "../game_object.hpp"

void AnimationComponent::update(Game& game, Renderer& renderer, UserCommand& userCommand) {
  std::shared_ptr<GameObject> owner = m_ownerObject.lock();

  std::vector<Frame> frames = getFrames();
  Frame currentFrame = frames[m_currentFrame];
  owner->m_currentTexture = currentFrame.texture;

  m_animationTime += 0.015f;
  if (m_animationTime > currentFrame.duration) {
    m_animationTime = 0.0f;
    if (m_currentFrame + 1 == frames.size()) {
      m_currentFrame = 0;
    } else {
      m_currentFrame += 1;
    }
  }
}

std::vector<Frame> AnimationComponent::getFrames() {
  return m_animations[m_animationPrefix + m_animationSuffix];
}

void AnimationComponent::changePrefix(std::string prefix) {
  if (prefix != m_animationPrefix) {
    m_currentFrame = 0;
  }
  m_animationPrefix = prefix; 
}

void AnimationComponent::changeSuffix(std::string suffix) {
  if (suffix != m_animationSuffix) {
    m_currentFrame = 0;
  }
  m_animationSuffix = suffix; 
}
