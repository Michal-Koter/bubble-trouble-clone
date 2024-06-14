//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_TEXTUREMANAGER_H
#define MYGAME_TEXTUREMANAGER_H

#include "Game.h"

class TextureManager {
public:
    static std::shared_ptr<SDL_Texture> LoadTexture(const std::string &fileName);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
    static void Draw(SDL_Texture* texture);
};


#endif //MYGAME_TEXTUREMANAGER_H
