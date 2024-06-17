#include "SDL2/SDL.h"
#include <iostream>
#include <vector>
#include "Game.h"

Game *game = nullptr;
int level = 1;

int main(int argc, char *argv[]) {
    bool multiplayer = false;
    if (argc > 1 && std::string(argv[1]) == "multi") multiplayer = true;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, multiplayer, level);

    while (Game::getPlayerLives() > 0) {
        game->init();

        while (game->running()) {
            frameStart = SDL_GetTicks();

            game->handleEvents();
            game->update();
            game->render();

            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
        game->clear();
    }

    game->destroy();

    return 0;
}