//
// Created by koter on 16.06.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_LIVECOMPONENT_H
#define CMAKE_INSTALL_CMAKE_LIVECOMPONENT_H

#include "Components.h"

#define LIVE_SIZE 32

class LiveComponent : public Component {
public:
    LiveComponent(int id) {
        if (id == FIRST_PLAYER_ID) {
            startX = 32;
        } else if (id == SECOND_PLAYER_ID) {
            startX = 656;
        }
    }

    void init() override {
        fullHeart = TextureManager::LoadTexture(fullHeartPath);
        emptyHeart = TextureManager::LoadTexture(emptyHeartPath);

        srcRect = {0, 0, LIVE_SIZE, LIVE_SIZE};
        destRec = {startX, SCREEN_HEIGHT - 96, LIVE_SIZE, LIVE_SIZE};
    }

    void draw() override {
        for (int i = 0; i < maxLives; ++i) {
            destRec.x = startX + 40 * i;
            if (i < remainingLives) {
                TextureManager::Draw(fullHeart.get(), srcRect, destRec);
            } else {
                TextureManager::Draw(emptyHeart.get(), srcRect, destRec);
            }
        }
    }

    void lossLive() {
        remainingLives--;
    }

    void zeroLives() {
        remainingLives = 0;
    }

    int getLives() {
        return remainingLives;
    }

private:
    int maxLives = 3;
    int remainingLives = 3;
    int startX = 32;

    std::string fullHeartPath = "assets/heart.bmp";
    std::string emptyHeartPath = "assets/heart_container.bmp";

    std::shared_ptr<SDL_Texture> fullHeart;
    std::shared_ptr<SDL_Texture> emptyHeart;

    SDL_Rect srcRect, destRec;
};

#endif //CMAKE_INSTALL_CMAKE_LIVECOMPONENT_H
