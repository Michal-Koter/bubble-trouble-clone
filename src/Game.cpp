//
// Created by koter on 02.06.2024.
//

#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"

std::shared_ptr<SDL_Texture> background;
Map *map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

Game::Game() {}

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

    map = new Map();

    player.addComponent<TransformComponent>(); // setting the start position using constructor doesn't work. Why? IDK!
    player.getComponent<TransformComponent>().setPos(500, 100);
    player.addComponent<SpriteComponent>("assets/player.bmp");
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
    manager.refresh();
    manager.update();
    player.getComponent<TransformComponent>().position.Add(Vector2D(5,0));
//    std::cout << player.getComponent<TransformComponent>() << std::endl;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    map->DrawMap();

    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


