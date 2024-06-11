//
// Created by koter on 09.06.2024.
//

#ifndef MYGAME_COLLISION_H
#define MYGAME_COLLISION_H

#include "SDL.h"

class  ColliderComponent;

class Collision {
public:
    static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB); //axis-aligned bounding boxes
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
private:
};
#endif //MYGAME_COLLISION_H
