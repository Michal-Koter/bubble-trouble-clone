//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_MAP_H
#define MYGAME_MAP_H

#include "Game.h"

class Map {
public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();
private:
    SDL_Rect src, dest;
    std::shared_ptr<SDL_Texture> backgroundTexture;
    std::shared_ptr<SDL_Texture> tileTexture;

    int map[20][25];
};


#endif //MYGAME_MAP_H
