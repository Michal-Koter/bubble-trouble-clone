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

    TransformComponent() {
        position.x = 0;
        position.y = 0;
    }

    TransformComponent(double x, double y) {
        position.x = x;
        position.y = y;
    }

    void init() override {
        position.x = 0;
        position.y = 0;
    }

//    void update() override {
//        position
//    }

    void setPos(double x, double y) {
        position.x = x;
        position.y = y;
    }
};

#endif //MYGAME_TRANSFORMCOMPONENT_H
