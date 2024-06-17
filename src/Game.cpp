//
// Created by koter on 02.06.2024.
//
#include <iostream>
#include "Game.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "Group.h"

Map *map;
SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent *> Game::colliders;

Manager manager;
//auto &background(manager.addEntity());
//std::vector<Entity*> players;

auto &player1(manager.addEntity());
auto &spear1(manager.addEntity());

auto &player2(manager.addEntity());
auto &spear2(manager.addEntity());


Game::Game(const char *title, int xpos, int ypos, int width, int height, bool multiplayer) {
    this->multiplayer = multiplayer;

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        }
        isRunning = true;
    } else {
        isRunning = false;
        return;
    }
    createPlayers();

    if (this->multiplayer) {

    }

}

Game::~Game() {}

void Game::init() {
    isRunning = true;

    map = new Map();

    if (!multiplayer) {
        player1.getComponent<TransformComponent>().setPosition(384, 448);
        spear1.getComponent<TransformComponent>().setPosition(-100, 0);
    } else {
        player1.getComponent<TransformComponent>().setPosition(264, 448);
        spear1.getComponent<TransformComponent>().setPosition(-100, 0);

        player2.getComponent<TransformComponent>().setPosition(504, 448);
        spear2.getComponent<TransformComponent>().setPosition(-100, 0);
    }

    auto &ball(manager.addEntity());
    ball.addComponent<TransformComponent>(384, 300, 24, 24, 3);
    ball.getComponent<TransformComponent>().setVelocity(55, 10);
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
            player1.getComponent<LiveComponent>().zeroLives();
            if (multiplayer) player2.getComponent<LiveComponent>().zeroLives();
            break;
        default:
            break;
    }
}

//auto& tiles(manager.getGroup(GROUP_MAP));
auto &players(manager.getGroup(GROUP_PLAYERS));
auto &balls(manager.getGroup(GROUP_BALLS));
//auto& colliders(manager.getGroup(GROUP_COLLIDERS));
auto &spears = (manager.getGroup(GROUP_SPEARS));
//std::vector<Entity*>* collection[4] = {&tiles, &spears, &balls, &players};
std::vector<Entity *> *collection[3] = {&spears, &balls, &players};

void Game::update() {
    manager.refresh();
//    manager.update();

    for (auto p: players) {
        auto oldTransform = p->getComponent<TransformComponent>();

        p->update();

        for (auto b: balls) {
            if (Collision::RectBall(p->getComponent<ColliderComponent>(), b->getComponent<ColliderComponent>())) {
                std::cout << "bal hit!" << std::endl;
                p->getComponent<LiveComponent>().lossLive();
                this->isRunning = false;
                return;
            }
        }

        if (Collision::FrameCollision(p->getComponent<ColliderComponent>())) {
            p->getComponent<TransformComponent>().setPosition(oldTransform.position.x, oldTransform.position.y);
            p->getComponent<TransformComponent>().setVelocity(0, 0);
        }
    }

    for (auto s: spears) {
        s->update();

        for (auto b: balls) {
            if (Collision::RectBall(s->getComponent<ColliderComponent>(), b->getComponent<ColliderComponent>())) {
                s->getComponent<SpearComponent>().moveOutOfFrame();

                b->getComponent<BallComponent>().split(manager);
            }
        }
    }

    // game exit if all balls are destroyed
//    if (balls.empty()) exit(0);
    for (auto b: balls) {
        auto oldTransform = b->getComponent<TransformComponent>();

        b->update();

        if (Collision::Ceiling(b->getComponent<ColliderComponent>())) {
            b->destroy();
        }

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

    for (auto &vec: collection) {
        for (auto &entity: *vec) {
            entity->draw();
        }
    }

    SDL_RenderPresent(renderer);
}

void Game::clear() {
    for (auto b: balls) {
        b->destroy();
    }
//    for(auto t: tiles) {
//        t->destroy();
//    }
}

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::createPlayers() const {
    player1.addComponent<TransformComponent>(384, 448);
    player1.addComponent<SpriteComponent>("assets/player_1.bmp");
    player1.addComponent<ColliderComponent>("player1");
    player1.addComponent<LiveComponent>(32);
    player1.addComponent<KeyboardMoveController>(1);
    player1.addComponent<NametagComponent>(1);
    player1.addGroup(GROUP_PLAYERS);

    spear1.addComponent<TransformComponent>(-20, 0, 450, 9, 1);
    spear1.addComponent<SpriteComponent>("assets/spear.bmp");
    spear1.addComponent<ColliderComponent>("spear1");
    spear1.addComponent<SpearComponent>();
    spear1.addComponent<KeyboardSpearController>(1, player1.getComponent<TransformComponent>());
    spear1.addGroup(GROUP_SPEARS);

    if (multiplayer) {
        player2.addComponent<TransformComponent>(384, 448);
        player2.addComponent<SpriteComponent>("assets/player_2.bmp");
        player2.addComponent<ColliderComponent>("player2");
        player2.addComponent<LiveComponent>(656);
        player2.addComponent<KeyboardMoveController>(2);
        player2.addComponent<NametagComponent>(2);
        player2.addGroup(GROUP_PLAYERS);

        spear2.addComponent<TransformComponent>(-20, 0, 450, 9, 1);
        spear2.addComponent<SpriteComponent>("assets/spear.bmp");
        spear2.addComponent<ColliderComponent>("spear2");
        spear2.addComponent<SpearComponent>();
        spear2.addComponent<KeyboardSpearController>(2, player2.getComponent<TransformComponent>());
        spear2.addGroup(GROUP_SPEARS);
    }
}

//void Game::AddTile(int id, int x, int y) {
//    auto& tile(manager.addEntity());
//
//    tile.addComponent<TileComponent>(x,y,32,32,id);
//    tile.addComponent<ColliderComponent>("dirt");
//    tile.addGroup(GROUP_MAP);
//}

int Game::getPlayerLives() {
    int min = 100;
    for (auto p: players) {
        int lives = p->getComponent<LiveComponent>().getLives();
        if (lives < min) min = lives;
    }
    return min;
}
