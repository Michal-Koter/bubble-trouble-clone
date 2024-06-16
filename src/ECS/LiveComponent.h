//
// Created by koter on 16.06.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_LIVECOMPONENT_H
#define CMAKE_INSTALL_CMAKE_LIVECOMPONENT_H

#include "Components.h"

#define TILE_SIZE 32

class LiveComponent : public Component {
public:
    void init() override {
        fullHeart = TextureManager::LoadTexture(fullHeartPath);
        emptyHeart = TextureManager::LoadTexture(emptyHeartPath);

        srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
        destRec = {32, 640 - TILE_SIZE * 3, TILE_SIZE, TILE_SIZE};
    }

    void draw() override {
        for (int i = 0; i < maxLives; ++i) {
            destRec.x = TILE_SIZE * (i + 1) + 8 * i;
            if (i <= remainingLives) {
                TextureManager::Draw(fullHeart.get(), srcRect, destRec);
            } else {
                TextureManager::Draw(emptyHeart.get(), srcRect, destRec);
            }
        }
    }

    void lossHeart() {
        remainingLives--;
    }

private:
    int maxLives = 3;
    int remainingLives = 3;

    std::string fullHeartPath = "assets/heart.bmp";
    std::string emptyHeartPath = "assets/heart_container.bmp";

    std::shared_ptr<SDL_Texture> fullHeart;
    std::shared_ptr<SDL_Texture> emptyHeart;

    SDL_Rect srcRect, destRec;
};

#endif //CMAKE_INSTALL_CMAKE_LIVECOMPONENT_H
