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
    Game(const char *title, int xpos, int ypos, int width, int height);

    ~Game();

    void init();

    void handleEvents();

    void update();

    void render();

    void clear();

    void destroy();

    bool running() { return isRunning; }

//    static void AddTile(int id, int x, int y);
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static std::vector<ColliderComponent*> colliders;
    static int getPlayerLives();
//    static void SplitBall(Vector2D pos, Vector2D vol, Vector2D acc, int scale);

private:
    bool isRunning;
    SDL_Window *window;
};


#endif //MYGAME_GAME_H
