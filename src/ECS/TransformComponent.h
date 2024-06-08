//
// Created by koter on 07.06.2024.
//

#ifndef MYGAME_TRANSFORMCOMPONENT_H
#define MYGAME_TRANSFORMCOMPONENT_H

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;

    int speed = 3;

    TransformComponent() {
        position.x = 0;
        position.y = 0;
        init();
    }

    TransformComponent(double x, double y) {
        position.x = x;
        position.y = y;
        init();
    }

    void init() override {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

    void setPos(double x, double y) {
        position.x = x;
        position.y = y;
    }
};

#endif //MYGAME_TRANSFORMCOMPONENT_H
