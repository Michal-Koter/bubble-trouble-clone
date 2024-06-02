//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_GAMEOBJECT_H
#define MYGAME_GAMEOBJECT_H

#include "Game.h"

struct vect {
    double x;
    double y;
};

class GameObject {
public:
    GameObject(const std::string &texturesheet, SDL_Renderer *ren, int x, int y);

    ~GameObject();

    void Update();
    void Render();

private:
    vect pos;
    std::shared_ptr<SDL_Texture> objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer *renderer;
};


#endif //MYGAME_GAMEOBJECT_H
