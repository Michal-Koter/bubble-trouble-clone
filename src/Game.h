//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include "SDL2/SDL.h"
#include <cstdio>
#include <memory>
#include <stdexcept>

class Game {

public:
    Game();

    ~Game();

    void init(const char *title, int xpos, int ypos, int width, int height);

    void handleEvents();

    void update();

    void render();

    void clear();

    bool running() { return isRunning; }

    static SDL_Renderer *renderer;

private:
//    double dt;
    int game_time;
    bool isRunning;
    SDL_Window *window;

};


#endif //MYGAME_GAME_H
