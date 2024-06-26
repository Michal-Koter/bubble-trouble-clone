cmake_minimum_required(VERSION 3.5)
project(mygame)

# Create an option to switch between a system sdl library and a vendored sdl library
option(MYGAME_VENDORED "Use vendored libraries" ON)

if(MYGAME_VENDORED)
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
    find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)

    # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
    find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
endif()

# Create your game executable target as usual
add_executable(mygame WIN32 src/main.cpp
        src/Game.cpp
        src/Game.h
        src/TextureManager.cpp
        src/TextureManager.h
        src/Map.cpp
        src/Map.h
        src/ECS/ECS.h
        src/ECS/Components.h
        src/ECS/SpriteComponent.h
        src/ECS/TransformComponent.h
        src/Vector2D.cpp
        src/Vector2D.h
        src/ECS/KeyboardMoveController.h
        src/ECS/ColliderComponent.h
        src/Collision.h
        src/Collision.cpp
        src/ECS/ECS.cpp
        src/ECS/BallComponent.h
        src/ECS/SpearComponent.h
        src/Group.h
        src/ECS/LiveComponent.h
        src/ECS/KeyboardSpearController.h
        src/ECS/NametagComponent.h
)

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(mygame PRIVATE SDL2::SDL2main)
endif()

# Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
target_link_libraries(mygame PRIVATE SDL2::SDL2)

add_compile_definitions(FIRST_PLAYER_ID=1 SECOND_PLAYER_ID=2 TILE_SIZE=32 SCREEN_WIDTH=800 SCREEN_HEIGHT=640)