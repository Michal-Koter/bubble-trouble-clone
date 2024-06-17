//
// Created by koter on 02.06.2024.
//

#ifndef MYGAME_GAME_H
#define MYGAME_GAME_H

#include "SDL2/SDL.h"
#include "Vector2D.h"
//#include "ECS/ECS.h"
//#include "ECS/Components.h"
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>

class ColliderComponent;

class Game {

public:
    Game(const char *title, int xpos, int ypos, int width, int height, bool multiplayer, int lvl);

    ~Game();

    void init();

    void handleEvents();

    void update();

    void render();

    void clear();

    void destroy();

    bool running() { return isRunning; }

    void createPlayers() const;

    static void createBall(int x, int y, int sc, int direction);

    static int getPlayerLives();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent *> colliders;

private:
    bool isRunning;
    bool multiplayer;
    int lvl;
    SDL_Window *window;
};


#endif //MYGAME_GAME_H
