//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include <SDL.h>
#include <stdio.h>

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

private:
    double dt;
    double game_time;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

};


#endif //MYGAME_GAME_H
