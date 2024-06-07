//
// Created by koter on 07.06.2024.
//

#ifndef MYGAME_SPRITECOMPONENT_H
#define MYGAME_SPRITECOMPONENT_H

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"

class SpriteComponent : public  Component {
public:
    SpriteComponent() = default;
    SpriteComponent(std::string path) {
        setTexture(path);
    }

    void setTexture(std::string path) {
        texture = TextureManager::LoadTexture(path);
    }

    void init() override {
        position = &entity->getComponent<PositionComponent>();

        srcRect = {0, 0, 32, 64};
        destRec = {0, 0, 32, 64};
    }

    void update() override {
        destRec.x = position->x();
        destRec.y = position->y();
    }

    void draw() override {
        TextureManager::Draw(texture.get(), srcRect, destRec);
    }

private:
    PositionComponent *position;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect srcRect, destRec;
};

#endif //MYGAME_SPRITECOMPONENT_H
