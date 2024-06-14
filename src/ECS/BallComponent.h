//
// Created by koter on 13.06.2024.
//

#ifndef MYGAME_BOUNCECOMPONENT_H
#define MYGAME_BOUNCECOMPONENT_H

#include "Components.h"

class BallComponent : public Component {
public:
    TransformComponent* transform{};

    BallComponent() = default;

    void init() override {
        if (!entity->hasComponents<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    void wallBounce(const TransformComponent& oldTransform) const {
        transform->setPosition(oldTransform.position.x, oldTransform.position.y);
        transform->setVelocity(-oldTransform.velocity.x, oldTransform.velocity.y);
        transform->setAcceleration(-oldTransform.acceleration.x, oldTransform.acceleration.y);
    }

    void floorBounce(const TransformComponent& oldTransform) const {
        transform->setPosition(oldTransform.position.x, oldTransform.position.y);
        transform->setVelocity(oldTransform.velocity.x, 0.);
        transform->setAcceleration(0., -8000);
    }

    void inAir() const {
        transform->setAcceleration(0., 100);
    }

};

#endif //MYGAME_BOUNCECOMPONENT_H
