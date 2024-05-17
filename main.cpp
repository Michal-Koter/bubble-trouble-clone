#include <SDL.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>


std::shared_ptr<SDL_Texture> load_image(SDL_Renderer *renderer, const std::string &file_name) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = SDL_LoadBMP(file_name.c_str());
    if (!surface) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create surface from image: %s", SDL_GetError());
        throw std::invalid_argument(SDL_GetError());
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format,0, 255, 255));
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

int main(int argc, char *argv[])
{
    using namespace std::chrono_literals;
    using namespace std::chrono;
    using namespace  std;
    SDL_Window *window;
    SDL_Renderer *renderer;

    double dt = 1./60.;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    auto player_texture = load_image(renderer, "player.bmp");
    auto clouds_texture = load_image(renderer, "clouds.bmp");
    auto background_texture = load_image(renderer, "background.bmp");

    bool still_playing = true;
    int x = 100;
    int y = 100;
    double game_time = 0.;
    steady_clock::time_point current_time = steady_clock::now();
    while (still_playing) {
        // events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    still_playing = false;
                break;
                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_Q) still_playing = false;
                    break;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    break;
            }
        }

        // physics

        game_time += dt;

        // graphics
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture.get(), NULL, NULL);
        SDL_Rect clouds_rect = {x/5,y/5,10000, 2000};
        SDL_RenderCopy(renderer, clouds_texture.get(), NULL, &clouds_rect);
        SDL_Rect player_rect = {x,y,64, 128};
        SDL_RenderCopyEx(renderer, player_texture.get(), NULL, &player_rect,game_time*360, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(renderer);
        // delays

        current_time = current_time + microseconds((long long int)(dt*1000000.0));
        std::this_thread::sleep_until(current_time);

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}