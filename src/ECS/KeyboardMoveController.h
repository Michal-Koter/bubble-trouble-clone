//
// Created by koter on 08.06.2024.
//

#ifndef MYGAME_KEYBOARDCONTROLLER_H
#define MYGAME_KEYBOARDCONTROLLER_H

#include "../Game.h"
#include "../Group.h"
#include "Components.h"
#include "SpearComponent.h"

class KeyboardMoveController : public Component {
public:
    TransformComponent *transform{};

    KeyboardMoveController(int id) {
        this->id = id;
    }

    void init() override {
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        if (id == 1) firstPlayer();
        if (id == 2) secondPlayer();
    }

    void firstPlayer() const {
        if(Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_LEFT:
                    transform->velocity.x = -70;
                    break;
                case SDLK_RIGHT:
                    transform->velocity.x = 70;
                    break;
                case SDLK_UP:

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
                default:
                    break;
            }
        }
    }

    void secondPlayer() const {
        if(Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_a:
                    transform->velocity.x = -70;
                    break;
                case SDLK_d:
                    transform->velocity.x = 70;
                    break;
                default:
                    break;
            }
        }
        if (Game::event.type == SDL_KEYUP) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_a:
                    transform->velocity.x = 0;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    break;
                default:
                    break;
            }
        }
    }
private:
    int id;
};

#endif //MYGAME_KEYBOARDCONTROLLER_H
