//
// Created by koter on 02.06.2024.
//

#include "TextureManager.h"

std::shared_ptr<SDL_Texture> TextureManager::LoadTexture(const std::string &fileName, SDL_Renderer *renderer) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP(fileName.c_str());
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