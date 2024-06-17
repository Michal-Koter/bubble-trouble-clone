//
// Created by koter on 09.06.2024.
//

#ifndef MYGAME_COLLISION_H
#define MYGAME_COLLISION_H

#include "ECS/ECS.h"
#include "SDL.h"
#include <memory>

class ColliderComponent;

class Collision {
public:
    static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB); //axis-aligned bounding boxes
    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);

    static bool FrameCollision(const ColliderComponent &col);

    static bool XFrameCollision(const ColliderComponent &col);

    static bool Flor(const ColliderComponent &col);

    static bool Ceiling(const ColliderComponent &col);

    static bool RectBall(const ColliderComponent &rect, const ColliderComponent &ball);
};

#endif //MYGAME_COLLISION_H
