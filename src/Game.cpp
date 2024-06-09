//
// Created by koter on 02.06.2024.
//
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

std::shared_ptr<SDL_Texture> background;
Map *map;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto &player(manager.addEntity());
auto &wall(manager.addEntity());
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
Game::Game() {}

Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    map = new Map();

    tile0.addComponent<TileComponent>(200,200,32,32,0);
    tile1.addComponent<TileComponent>(250,250,32,32,0);
    tile1.addComponent<ColliderComponent>("dirt");

    player.addComponent<TransformComponent>(); // setting the start position using constructor doesn't work. Why? IDK!
    player.getComponent<TransformComponent>().setPos(100, 100);
    player.addComponent<SpriteComponent>("assets/player.bmp");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(350., 100., 300, 400, 1);
    wall.addComponent<SpriteComponent>("assets/spear.bmp");
    wall.addComponent<ColliderComponent>("spear");
}

void Game::handleEvents() {

    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }

}

void Game::update() {
    manager.refresh();
    manager.update();

    for (auto cc : colliders) {
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
    }
    if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
                        wall.getComponent<ColliderComponent>().collider)) {
//       player.getComponent<TransformComponent>().scale = 2;
        player.getComponent<TransformComponent>().velocity * -1;
        std::cout << "Wall hit!" << std::endl;
    }
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


