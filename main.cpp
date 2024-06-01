#include <SDL.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>


#define TILE_SIZE 25

struct game_map_t {
    int width, height;
    std::vector<int> map;
    int get(int x, int y) const  {
        if (x < 0) return 1;
        if (x >= width) return 1;
        if (y < 0) return 1;
        if (y >= height) return 1;
        return map[y*width+x];
    }
};

game_map_t game_map = {
        36, 20, {
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1

        }
};

std::shared_ptr<SDL_Texture> load_image(SDL_Renderer *renderer, const std::string &file_name) {
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

struct vect_t {
    double x;
    double y;
};

vect_t operator+(const vect_t a, const vect_t b) {
    vect_t ret = a;
    ret.x += b.x;
    ret.y += b.y;
    return ret;
}
vect_t operator*(const vect_t a, const double b) {
    vect_t ret = a;
    ret.x *= b;
    ret.y *= b;
    return ret;
}

struct player_t {
    vect_t p; ///< position
    vect_t v; ///< velocity
    vect_t a; ///< acceleration
};


struct spear_t {
    vect_t p;
    vect_t v;
    vect_t a;
    bool isOnScreen;
};

bool is_in_collision(vect_t pos, const game_map_t &map) {
    return map.get(pos.x, pos.y) > 0;
}

bool is_on_the_ground(player_t player, const game_map_t &map) {
    return map.get(player.p.x, player.p.y+0.01) > 0;
}

player_t update_player(player_t player_old, const game_map_t &map, double dt) {
    player_t player = player_old;

    if (!is_on_the_ground (player_old, map)) player_old.a.y = 10; // przyspieszenie ziemskie (w powietrzu)

    player.p = player_old.p + (player_old.v * dt) + (player_old.a*dt*dt)*0.5;
    player.v = player_old.v + (player_old.a * dt);
    player.v.x =  player.v.x * 0.99;

    /// TODO: Nalezaloby rozbudowac liste punktow kolizji aby to mialo sens.
    std::vector<vect_t> collision_points = {
            {-0.5,.5},
            {0.5,.5},
            {-0.5, 0.5},
            {0.7, 0.5}
    };
    std::vector<vect_t> collision_mods = {
            {0.0,-1.0},
            {0.0,-1.0},
            {-1, 0.},
            {-1,0.}
    };

    for (int i = 0; i < collision_points.size(); i++) {
        auto test_point = player.p + collision_points[i];

        if (is_in_collision(test_point, map)) {
            if(collision_mods[i].y < 0) {
                player.v.y = 0;
                player.p.y = player_old.p.y;
            }
            if(collision_mods[i].x <0) {
                player.v.x = 0;
                player.a.x = 0;
                player.p.x = player_old.p.x;
            }
        }
    }

    return player;
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

    if (SDL_CreateWindowAndRenderer(900, 500, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    auto player_texture = load_image(renderer, "assets/player.bmp");
    auto background_texture = load_image(renderer, "assets/background.bmp");
    auto spear_texture = load_image(renderer, "assets/spear.bmp");

    bool still_playing = true;

    player_t player;
    player.p.x = 18;
    player.p.y = 10;
    player.a.x = 0;
    player.a.y = 0;
    player.v.x = 0;
    player.v.y = 0;

    spear_t spear;
    spear.p.x = -1;
    spear.p.y = -1;
    spear.a.x = 0;
    spear.a.y = 0;
    spear.v.x = 0;
    spear.v.y = 0;
    spear.isOnScreen = false;

//    int x = 450;
//    int y = 425;
    double game_time = 0.;
    bool show_spear = false;
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
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) { show_spear = !show_spear; spear.a.y=-50; };
//                    if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) { spear.a.y = 50; spear.p.x };
                    if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) player.v.x = -5;
                    if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) player.v.x = 5;
                    break;
            }
        }

        // physics

        game_time += dt;

        player = update_player(player, game_map, dt);

        // graphics
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_texture.get(), NULL, NULL);

        if (show_spear) {
            SDL_Rect spear_rect = {(int)(player.p.x*TILE_SIZE-(TILE_SIZE/2)+12),(int)(player.p.y*TILE_SIZE-TILE_SIZE+54), 9, 330};
            SDL_RenderCopyEx(renderer, spear_texture.get(), NULL, &spear_rect, 0, NULL, SDL_FLIP_NONE);
        }

        SDL_Rect player_rect = {(int)(player.p.x*TILE_SIZE-(TILE_SIZE/2)),(int)(player.p.y*TILE_SIZE-TILE_SIZE),32, 64};
        {
            int r = 0, g = 0, b = 0;
            if (is_on_the_ground(player, game_map)) {
                r = 255;
            }
            if (is_in_collision(player.p, game_map)) {
                g = 255;
            }
            SDL_SetRenderDrawColor(renderer, r,g,b, 0xFF);
        }
        SDL_RenderDrawRect(renderer,  &player_rect);
        SDL_RenderCopyEx(renderer, player_texture.get(), NULL, &player_rect,0, NULL, SDL_FLIP_NONE);

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