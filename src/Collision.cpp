//
// Created by koter on 09.06.2024.
//

#include "Collision.h"
#include "ECS\ColliderComponent.h"
#include <cmath>

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB) {
    return ( rectA.x + rectA.w >= rectB.x &&
             rectB.x + rectB.w >= rectA.x &&
             rectA.y + rectA.h >= rectB.y &&
             rectB.y + rectB.h >= rectA.y );
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB) {
    if ( AABB(colA.collider, colB.collider)) {
//        std::cout << colA.tag << " hit: " << colB.tag << std::endl;
        return true;
    }

    return false;
}

bool Collision::FrameCollision(const ColliderComponent& col) {
    return (XFrameCollision(col) || Flor(col));
}

bool Collision::XFrameCollision(const ColliderComponent& col) {
    auto rect = col.collider;
    return (rect.x < 32 || rect.x+rect.w > 768);
}

bool Collision::Flor(const ColliderComponent& col) {
    auto rect = col.collider;
    return (rect.y+rect.h > 512);
}

bool Collision::Ceiling(const ColliderComponent &col) {
    auto rect = col.collider;
    return (rect.y< 32);
}

bool Collision::PlayerBall(const ColliderComponent& player, const std::vector<Entity*>& balls) {
    auto playerRect = player.collider;

    int numPoints = 100;
    double thetaStep = 2 * M_PI / numPoints;

    for (auto b : balls) {
        if (!AABB(player, b->getComponent<ColliderComponent>())) {
            continue;
        }

        int x0 = b->getComponent<TransformComponent>().position.x;
        int y0 = b->getComponent<TransformComponent>().position.y;
        double r = b->getComponent<TransformComponent>().width * b->getComponent<TransformComponent>().scale / 2;

        for (int i = 0; i < numPoints; ++i) {
            double theta = i * thetaStep;
            double x = x0 + r * cos(theta);
            double y = y0 + r * sin(theta);

            if (x >= playerRect.x && x <= playerRect.x+playerRect.w && y >= playerRect.y && y <= playerRect.y+playerRect.h) {
                return true;
            }
        }
    }

    return false;
}