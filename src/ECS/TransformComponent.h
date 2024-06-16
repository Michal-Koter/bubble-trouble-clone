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
    Vector2D acceleration;

    int height = 64;
    int width = 32;
    int scale = 1;

    int speed = 3;
    double dt = 1./60.;

    TransformComponent() {
        position.Zero();
    }

    TransformComponent(int sc) {
        position.Zero();
        scale = sc;
    }

    TransformComponent(double x, double y) {
        setPosition(x, y);
    }

    TransformComponent(double x, double y, int h, int w, int sc) {
        setPosition(x, y);
        width = w;
        height = h;
        scale = sc;
    }

    void init() override {
        velocity.Zero();
        acceleration.Zero();
    }

    void update() override {
//        position.x += velocity.x * speed;
//        position.y += velocity.y * speed;

        position.x = position.x + (velocity.x * dt) + (acceleration.x*dt*dt)*0.5;
        velocity.x = velocity.x + (acceleration.x * dt)*scale/.8;

        position.y = position.y + (velocity.y * dt) + (acceleration.y*dt*dt)*0.5;
        velocity.y = velocity.y + (acceleration.y * dt)*scale/1.2;
    }

    void setPosition(double x, double y) {
        position.x = x;
        position.y = y;
    }

    void setPosition(const Vector2D vec) {
        position = vec;
    }

    void setVelocity(double x, double y) {
        velocity.x = x;
        velocity.y = y;
    }

    void setAcceleration(double x, double y) {
        acceleration.x = x;
        acceleration.y = y;
    }
};

#endif //MYGAME_TRANSFORMCOMPONENT_H
