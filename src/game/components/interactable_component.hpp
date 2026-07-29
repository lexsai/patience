#ifndef PATIENCE_GAME_COMPONENTS_INTERACTABLE_COMPONENT_HPP
#define PATIENCE_GAME_COMPONENTS_INTERACTABLE_COMPONENT_HPP

#include "component.hpp"

class InteractableComponent: public Component {
  public:
    explicit InteractableComponent(std::shared_ptr<GameObject>& gameObject): 
      Component{ ComponentId::Interactable, gameObject } {}

    void update(Game& game, Renderer& renderer, UserCommand& userCommand) override;
};

#endif
