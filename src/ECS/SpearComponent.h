//
// Created by koter on 14.06.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_SPEARCOMPONENT_H
#define CMAKE_INSTALL_CMAKE_SPEARCOMPONENT_H


#include "Components.h"

class SpearComponent : public Component {
public:
    TransformComponent *transform{};
    int speed = 2;

    SpearComponent() = default;

    void init() override {
        if (!entity->hasComponents<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        if (transform->position.y < 32) {
            moveOutOfFrame();
        } else {
            transform->height += speed;
            transform->position.y -= speed;
        }
    }

    void startThrow(const TransformComponent& player) const {
        transform->position.x = player.position.x + int(player.width/2) - int(transform->width/2);
        transform->position.y = player.position.y; // maybe add constant int?
        transform->height = player.height;
    }

    void moveOutOfFrame() const {
        transform->setPosition(-10, 33);
    }
};
#endif //CMAKE_INSTALL_CMAKE_SPEARCOMPONENT_H
