//
// Created by koter on 13.06.2024.
//

#ifndef MYGAME_BOUNCECOMPONENT_H
#define MYGAME_BOUNCECOMPONENT_H

#include "Components.h"
#include "../Group.h"

#define BALL_SIZE 24
#define ACC_BOUNCE (-8000)

class BallComponent : public Component {
public:
    TransformComponent *transform{};

    BallComponent() = default;

    void init() override {
        if (!entity->hasComponents<TransformComponent>()) {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
    }

    void wallBounce(const TransformComponent &oldTransform) const {
        transform->setPosition(oldTransform.position.x, oldTransform.position.y);
        transform->setVelocity(-oldTransform.velocity.x, oldTransform.velocity.y);
        transform->setAcceleration(-oldTransform.acceleration.x, oldTransform.acceleration.y);
    }

    void floorBounce(const TransformComponent &oldTransform) const {
        transform->setPosition(oldTransform.position.x, oldTransform.position.y);
        transform->setVelocity(oldTransform.velocity.x, 0.);
        transform->setAcceleration(0., ACC_BOUNCE);
    }

    void inAir() const {
        transform->setAcceleration(0., 100);
    }

    void split(Manager &manager) {
        if (transform->scale > 1) {
            createBall(manager, false);
            createBall(manager, true);
        }
        entity->destroy();
    }

    void createBall(Manager &manager, bool direction) {
        int dir = (direction) ? 1 : -1;

        auto &newBall(manager.addEntity());
        newBall.addComponent<TransformComponent>(transform->position.x + 5 * transform->scale * dir,
                                                 transform->position.y, BALL_SIZE, BALL_SIZE,
                                                 transform->scale - 1);
        newBall.getComponent<TransformComponent>().setVelocity(transform->velocity.x * dir, 0);
        newBall.getComponent<TransformComponent>().setAcceleration(transform->acceleration.x,
                                                                   transform->acceleration.y + ACC_BOUNCE);
        newBall.addComponent<SpriteComponent>("assets/ball.bmp");
        newBall.addComponent<ColliderComponent>("ball");
        newBall.addComponent<BallComponent>();
        newBall.addGroup(GROUP_BALLS);
    }

};

#endif //MYGAME_BOUNCECOMPONENT_H
