//
// Created by koter on 02.06.2024.
//

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const std::string &texturesheet, int x, int y) {
    objTexture = TextureManager::LoadTexture(texturesheet);
    pos.x = x;
    pos.y = y;
}

GameObject::~GameObject() {}

void GameObject::Update() {
    pos.x++;
    pos.y++;

    srcRect.h = 64;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = pos.x;
    destRect.y = pos.y;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture.get(), &srcRect, &destRect);
}

