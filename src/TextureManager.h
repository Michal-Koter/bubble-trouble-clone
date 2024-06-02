//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_TEXTUREMANAGER_H
#define MYGAME_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
    static std::shared_ptr<SDL_Texture> LoadTexture(const std::string &fileName, SDL_Renderer *renderer);
};


#endif //MYGAME_TEXTUREMANAGER_H
