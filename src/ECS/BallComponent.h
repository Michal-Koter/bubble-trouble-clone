//
// Created by koter on 13.06.2024.
//

#ifndef MYGAME_BOUNCECOMPONENT_H
#define MYGAME_BOUNCECOMPONENT_H

#include "Components.h"
#include "../Group.h"

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

    void split(Manager& manager) {
        auto& leftBall(manager.addEntity());
        auto& rightBall(manager.addEntity());

        leftBall.addComponent<TransformComponent>(transform->position.x - 10, transform->position.y, 24, 24, transform->scale - 1);
        leftBall.getComponent<TransformComponent>().setVelocity(-transform->velocity.x, transform->velocity.y);
        leftBall.getComponent<TransformComponent>().setAcceleration(transform->acceleration.x, transform->acceleration.y - 500);
        leftBall.addComponent<SpriteComponent>("assets/ball.bmp");
        leftBall.addComponent<ColliderComponent>("ball");
        leftBall.addComponent<BallComponent>();
        leftBall.addGroup(GROUP_BALLS);

        rightBall.addComponent<TransformComponent>(transform->position.x + 10, transform->position.y, 24, 24, transform->scale - 1);
        rightBall.getComponent<TransformComponent>().setVelocity(transform->velocity.x, transform->velocity.y);
        rightBall.getComponent<TransformComponent>().setAcceleration(transform->acceleration.x, transform->acceleration.y - 500);
        rightBall.addComponent<SpriteComponent>("assets/ball.bmp");
        rightBall.addComponent<ColliderComponent>("ball");
        rightBall.addComponent<BallComponent>();
        rightBall.addGroup(GROUP_BALLS);

        transform->setPosition(-100,0);
        transform->velocity.Zero();
        transform->acceleration.Zero();
    }

};

#endif //MYGAME_BOUNCECOMPONENT_H
