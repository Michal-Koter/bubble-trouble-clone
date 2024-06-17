//
// Created by koter on 09.06.2024.
//

#include "Collision.h"
#include "ECS\ColliderComponent.h"
#include <cmath>

#define SINGLE_FRAME 32

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
    return (rectA.x + rectA.w >= rectB.x &&
            rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y &&
            rectB.y + rectB.h >= rectA.y);
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB) {
    return (AABB(colA.collider, colB.collider));
}

bool Collision::FrameCollision(const ColliderComponent &col) {
    return (XFrameCollision(col) || Flor(col));
}

bool Collision::XFrameCollision(const ColliderComponent &col) {
    auto rect = col.collider;
    return (rect.x < SINGLE_FRAME || rect.x + rect.w > SCREEN_WIDTH - SINGLE_FRAME);
}

bool Collision::Flor(const ColliderComponent &col) {
    auto rect = col.collider;
    return (rect.y + rect.h > SCREEN_HEIGHT - SINGLE_FRAME * 4);
}

bool Collision::Ceiling(const ColliderComponent &col) {
    auto rect = col.collider;
    return (rect.y < SINGLE_FRAME);
}

bool Collision::RectBall(const ColliderComponent &rect, const ColliderComponent &ball) {
    auto playerRect = rect.collider;

    int numPoints = 100;
    double thetaStep = 2 * M_PI / numPoints;


    if (!AABB(rect, ball)) {
        return false;
    }

    int x0 = ball.collider.x + ball.collider.w / 2;
    int y0 = ball.collider.y + ball.collider.h / 2;
    double r = ball.collider.w / 2;

    for (int i = 0; i < numPoints; ++i) {
        double theta = i * thetaStep;
        double x = x0 + r * cos(theta);
        double y = y0 + r * sin(theta);

        if (x >= playerRect.x && x <= playerRect.x + playerRect.w && y >= playerRect.y &&
            y <= playerRect.y + playerRect.h) {
            return true;
        }
    }
    return false;
}