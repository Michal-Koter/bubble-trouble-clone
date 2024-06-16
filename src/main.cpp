#include "SDL2/SDL.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;
    using namespace std::chrono;
    using namespace std;

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640);

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