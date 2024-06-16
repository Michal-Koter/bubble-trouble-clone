//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include "Game.h"
#include <string>

class Map {
public:
    Map();
    ~Map();

    void loadMap();
//    static void LoadMap(const std::string& path, int sizeX, int sizeY);
private:
    SDL_Rect src, dest;
    std::shared_ptr<SDL_Texture> backgroundTexture;
};


#endif //MYGAME_MAP_H
