//
// Created by koter on 02.06.2024.
//

#include "Map.h"
#include "TextureManager.h"

Map::Map() {
    backgroundTexture = TextureManager::LoadTexture("assets/bg_v2.bmp");
}

Map::~Map() {}

void Map::loadMap() {
    TextureManager::Draw(backgroundTexture.get());
}
