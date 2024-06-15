//
// Created by koter on 02.06.2024.
//
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "Group.h"

//std::shared_ptr<SDL_Texture> background;
Map *map;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto &background(manager.addEntity());
auto &player(manager.addEntity());
auto &spear(manager.addEntity());
auto &ball(manager.addEntity());



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
//    background.addComponent<TransformComponent>(0, 0, height, width, 1);
//    background.addComponent<SpriteComponent>("assets/background.bmp");
//    background.addGroup(GROUP_MAP);

//    Map::LoadMap("assets/basic.map", 25, 20);

    player.addComponent<TransformComponent>(384, 448);
    player.addComponent<SpriteComponent>("assets/player.bmp");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(GROUP_PLAYERS);

    spear.addComponent<TransformComponent>(-20, 0, 450, 9, 1);
    spear.addComponent<SpriteComponent>("assets/spear.bmp");
    spear.addComponent<ColliderComponent>("spear");
    spear.addComponent<SpearComponent>();
    spear.addGroup(GROUP_SPEARS);

    ball.addComponent<TransformComponent>(384,300,24,24,3);
    ball.getComponent<TransformComponent>().setVelocity(55,10);
    ball.addComponent<SpriteComponent>("assets/ball.bmp");
    ball.addComponent<ColliderComponent>("ball");
    ball.addComponent<BallComponent>();
    ball.addGroup(GROUP_BALLS);

}

void Game::handleEvents() {

    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE && spear.getComponent<TransformComponent>().position.x < 0) {
                spear.getComponent<SpearComponent>().startThrow(player.getComponent<TransformComponent>());
            }
            break;
        default:
            break;
    }

}

auto& tiles(manager.getGroup(GROUP_MAP));
auto& players(manager.getGroup(GROUP_PLAYERS));
auto& balls(manager.getGroup(GROUP_BALLS));
//auto& colliders(manager.getGroup(GROUP_COLLIDERS));
auto& spears(manager.getGroup(GROUP_SPEARS));
std::vector<Entity*>* collection[4] = {&tiles, &spears, &players, &balls};

void Game::update() {
    manager.refresh();
//    manager.update();

    for (auto p : players) {
        auto oldTransform = p->getComponent<TransformComponent>();

        p->update();

        for (auto b : balls) {
            if (Collision::RectBall(p->getComponent<ColliderComponent>(), b->getComponent<ColliderComponent>())) {
                std::cout << "bal hit!" << std::endl;
//                exit(1);
            }
        }

        if (Collision::FrameCollision(p->getComponent<ColliderComponent>())) {
            p->getComponent<TransformComponent>().setPosition(oldTransform.position.x, oldTransform.position.y);
            p->getComponent<TransformComponent>().setVelocity(0, 0);
        }
    }

    for (auto s : spears) {
        s->update();

        for (auto b : balls) {
            if (Collision::RectBall(s->getComponent<ColliderComponent>(), b->getComponent<ColliderComponent>())) {
                s->getComponent<SpearComponent>().moveOutOfFrame();

                b->getComponent<BallComponent>().split(manager);
            }
        }
    }

    // game exit if all balls are destroyed
    if (balls.empty()) exit(0);
    for (auto b : balls) {
        auto oldTransform = b->getComponent<TransformComponent>();

        b->update();
        if (Collision::Flor(b->getComponent<ColliderComponent>())) {
            b->getComponent<BallComponent>().floorBounce(oldTransform);
        } else {
            b->getComponent<BallComponent>().inAir();
        }

        if (Collision::XFrameCollision(b->getComponent<ColliderComponent>())) {
            b->getComponent<BallComponent>().wallBounce(oldTransform);
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);

    map->loadMap();

    for (auto& vec : collection) {
        for (auto& entity: *vec) {
            entity->draw();
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::AddTile(int id, int x, int y) {
    auto& tile(manager.addEntity());
    
    tile.addComponent<TileComponent>(x,y,32,32,id);
    tile.addComponent<ColliderComponent>("dirt");
    tile.addGroup(GROUP_MAP);
}
