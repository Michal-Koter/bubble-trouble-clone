//
// Created by koter on 02.06.2024.
//

#include "Game.h"
#include "GameObject.h"

GameObject *player;

SDL_Rect srcR, destR;

Game::Game() {
//    dt = 1./60.;
    game_time = 0;
}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255,0,255,255);
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    player = new GameObject("assets/player.bmp", renderer, 450, 300);
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.scancode == SDL_SCANCODE_Q) isRunning = false;
                break;
            case SDL_KEYDOWN:
                break;
        }
    }
}

void Game::update() {
//    game_time += dt;
    game_time++;

    player->Update();
}

void Game::render() {
    SDL_RenderClear(renderer);

    player->Render();

    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


