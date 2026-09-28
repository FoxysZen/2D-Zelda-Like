#include "core/GameLogic.h"
#include "graphics/RenderEngine.h"
#include "input/InputManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <iostream>

const int SCALE = 4;
const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 160;

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

int main (int argc, char *argv[])
{
    RenderEngine renderer;
    renderer.init("2D Zelda Like", SCREEN_WIDTH, SCREEN_HEIGHT, SCALE);

    InputManager inputManager;

    GameLogic game;
    game.init(SCALE, SCREEN_WIDTH, SCREEN_HEIGHT, inputManager);
    
    renderer.loadTexture(game.getPlayer()->getAtlasName());

    renderer.loadTexture(game.getTileMap()->getCurrentMap()->atlas);

    Uint64 lastStart = SDL_GetTicks64();

    bool debugFrames = false;
    bool stepNextFrame = false;
    
    while (game.isRunning())
    {
        Uint64 frameStart = SDL_GetTicks64();
        
        float deltaTime = (frameStart - lastStart) / 1000.0f;
        lastStart = frameStart;

        inputManager.processEvents(&game);

#ifndef DEBUG_MODE
        if (inputManager.isKeyPressed(SDL_SCANCODE_0))
        {
            debugFrames = !debugFrames;
            if (debugFrames)
            {
                std::cout << "[DEBUG] Stop time!" << std::endl;
            }
            else
            {
                std::cout << "[DEBUG] Resume time!" << std::endl;
            }
        }
        
        if (debugFrames && inputManager.isKeyPressed(SDL_SCANCODE_9))
        {
            stepNextFrame = true;
            std::cout << "[DEBUG] Frame step..." << std::endl;
        }

        if (!debugFrames)
        {
            game.update(deltaTime);
        }
        else if (stepNextFrame)
        {
            const float fixedDeltaTime = 1.0f / TARGET_FPS;
            game.update(fixedDeltaTime);
            
            stepNextFrame = false; 
        }

        renderer.render(&game);

        Uint32 frameTime = SDL_GetTicks64() - frameStart;
        if (FRAME_DELAY > frameTime)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
#endif
/*
        game.update(deltaTime);
        
        renderer.render(&game);

        // Limits to 60FPS
        Uint32 frameTime = SDL_GetTicks64() - frameStart;
        if (FRAME_DELAY > frameTime)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
*/
    }

    renderer.quit();
    return 0;
}
