//
// Created by koter on 09.06.2024.
//

#ifndef MYGAME_TILECOMPONENT_H
#define MYGAME_TILECOMPONENT_H

#include "ECS.h"
#include "SDL.h"

class TileComponent : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    std::string path;
    
    TileComponent() = default;
    
    TileComponent(int x, int y, int w, int h, int id) {
        tileRect = {x, y, w, h};
        tileID = id;

        switch (tileID) {
            case 1:
                path = "assets/tiles.bmp";
                break;
            default:
                path = "assets/background.bmp";
                break;
        }
    }
    
    void init() override {
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.h, tileRect.w, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }

};

#endif //MYGAME_TILECOMPONENT_H
