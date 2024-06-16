//
// Created by koter on 02.06.2024.
//

#include "Map.h"
#include "TextureManager.h"
#include <fstream>

#define TILE_SIZE 32

Map::Map() {
    backgroundTexture = TextureManager::LoadTexture("assets/bg_v2.bmp");
    
}

Map::~Map() {}

void Map::loadMap() {
    TextureManager::Draw(backgroundTexture.get());
}

//void Map::LoadMap(const std::string& path, int sizeX, int sizeY) {
//    char tile;
//    std::fstream mapFile;
//    mapFile.open(path);
//
//    for (int y = 0; y < sizeY; y++) {
//        for (int x = 0; x < sizeX; x++) {
//            mapFile.get(tile);
//            auto id = atoi(&tile);
//            if (id != 0) {
//                Game::AddTile(id, x * TILE_SIZE, y * TILE_SIZE);
//            }
//            mapFile.ignore();
//        }
//    }
//
//    mapFile.close();
//}
