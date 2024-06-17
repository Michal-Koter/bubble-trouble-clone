//
// Created by koter on 17.06.2024.
//

#ifndef CMAKE_INSTALL_CMAKE_KEYBOARDSPEARCONTROLLER_H
#define CMAKE_INSTALL_CMAKE_KEYBOARDSPEARCONTROLLER_H

#include "Components.h"

class KeyboardSpearController : public Component {
public:
    TransformComponent *spearTransform;
    TransformComponent *playerTransform;

    KeyboardSpearController(int id, TransformComponent &player) {
        this->id = id;
        playerTransform = &player;
    }

    void init() override {
        spearTransform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        if (id == FIRST_PLAYER_ID) firstPlayer();
        if (id == SECOND_PLAYER_ID) secondPlayer();
    }

    void firstPlayer() const {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_UP:
                    if (spearTransform->position.x < 0) {
                        entity->getComponent<SpearComponent>().startThrow(*playerTransform);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void secondPlayer() const {
        if (Game::event.type == SDL_KEYDOWN) {
            switch (Game::event.key.keysym.sym) {
                case SDLK_w:
                    if (spearTransform->position.x < 0) {
                        entity->getComponent<SpearComponent>().startThrow(*playerTransform);
                    }
                    break;
                default:
                    break;
            }
        }
    }

private:
    int id;
};

#endif //CMAKE_INSTALL_CMAKE_KEYBOARDSPEARCONTROLLER_H
