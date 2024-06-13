//
// Created by koter on 08.06.2024.
//

#ifndef MYGAME_KEYBOARDCONTROLLER_H
#define MYGAME_KEYBOARDCONTROLLER_H

#include "../Game.h"
#include "Components.h"

class KeyboardController : public Component {
public:
    TransformComponent *transform;

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
    }
    void update() override {
        if(Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_LEFT:
                    transform->velocity.x = -70;
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 70;
                    break;
                case SDLK_UP:
                    transform->velocity.y = -70;
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 70;
                    break;
                default:
                    break;
            }
        }
        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_LEFT:
                    transform->velocity.x = 0;
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 0;
                    break;
                case SDLK_UP:
                    transform->velocity.y = 0;
                    break;
                case SDLK_DOWN:
                    transform->velocity.y = 0;
                default:
                    break;
            }
        }
    }

};

#endif //MYGAME_KEYBOARDCONTROLLER_H
