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
        transform = &entity->getComponent<TransformComponent>();

        srcRect = {0, 0, 32, 64};
        destRec = {0, 0, 32, 64};
    }

    void update() override {
        destRec.x = (int)transform->position.x;
        destRec.y = (int)transform->position.y;
    }

    void draw() override {
        TextureManager::Draw(texture.get(), srcRect, destRec);
    }

private:
    TransformComponent *transform;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect srcRect, destRec;
};

#endif //MYGAME_SPRITECOMPONENT_H
