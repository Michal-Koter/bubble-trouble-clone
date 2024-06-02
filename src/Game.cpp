//
// Created by koter on 02.06.2024.
//

#include "Game.h"

std::shared_ptr<SDL_Texture> playerTexture;
std::shared_ptr<SDL_Texture> backgroundTexture;

SDL_Rect srcR, destR;

Game::Game() {
    dt = 1./60.;
    game_time = 0.;
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

    playerTexture = loadImage("assets/player.bmp");
    backgroundTexture = loadImage("assets/background.bmp");
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
    game_time += dt;

    destR.h = 64;
    destR.w = 32;
    destR.x = game_time;
}

void Game::render() {
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexture.get(), NULL, NULL);
    SDL_RenderCopy(renderer, playerTexture.get(), NULL, &destR);

    SDL_RenderPresent(renderer);
}

void Game::clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::shared_ptr<SDL_Texture> Game::loadImage(const std::string &file_name) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP(file_name.c_str());
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,255, 0, 255));
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_FreeSurface(surface);
    return {texture, [](SDL_Texture *t) {
        SDL_DestroyTexture(t);
    }};
}

