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

    game = new Game();
    game->init("My game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 500);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();

    }

    game->clear();

    return 0;
}