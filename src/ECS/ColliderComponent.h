//
// Created by koter on 09.06.2024.
//

#ifndef MYGAME_COLLIDERCOMPONENT_H
#define MYGAME_COLLIDERCOMPONENT_H

#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component {
public:
    SDL_Rect collider;
    std::string tag;

    TransformComponent* transform;

    ColliderComponent(const std::string t) {
        tag = t;
    }

    void init() override {
        if (!entity->hasComponents<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        Game::colliders.push_back(this);
    }

    void update() override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = static_cast<int>(transform->width * transform->scale);
        collider.h = static_cast<int>(transform->height * transform->scale);
    }

private:
};

#endif //MYGAME_COLLIDERCOMPONENT_H
