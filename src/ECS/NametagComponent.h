//
// Created by koter on 17.06.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_NAMETAGCOMPONENT_H
#define CMAKE_INSTALL_CMAKE_NAMETAGCOMPONENT_H

#include "Components.h"

#define NAMERTAG_SIZE 32

class NametagComponent : public Component {
public:
    NametagComponent(int id) {
        if (id == FIRST_PLAYER_ID) {
            startX = 32;
            path = "assets/nametag_1.bmp";
        } else if (id == SECOND_PLAYER_ID) {
            startX = 656;
            path = "assets/nametag_2.bmp";
        }
    }

    void init() override {
        texture = TextureManager::LoadTexture(path);

        srcRect = {0, 0, NAMERTAG_SIZE * 3, NAMERTAG_SIZE};
        destRec = {startX, SCREEN_HEIGHT - 60, 112, NAMERTAG_SIZE};
    }

    void draw() override {
        destRec.x = startX;
        TextureManager::Draw(texture.get(), srcRect, destRec);
    }

private:
    int startX = 32;
    std::string path;
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect srcRect, destRec;
};

#endif //CMAKE_INSTALL_CMAKE_NAMETAGCOMPONENT_H
