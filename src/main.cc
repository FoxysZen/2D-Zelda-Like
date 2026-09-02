#include "core/GameLogic.h"
#include "graphics/RenderEngine.h"
#include "input/InputManager.h"
#include <SDL2/SDL.h>

const int SCALE = 4;
const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 160;

const int TARGET_FPS = 60;
const int FRAME_DELAY = 1000 / TARGET_FPS;

int main (int argc, char *argv[])
{
    RenderEngine renderer;
    renderer.init("2D Zelda Like", SCREEN_WIDTH, SCREEN_HEIGHT, SCALE);

    GameLogic game;
    game.init(SCALE, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    renderer.loadTexture(game.getPlayer()->getAtlasName());

    renderer.loadTexture(game.getTileMap()->getCurrentMap()->atlas);

    Uint64 lastStart = SDL_GetTicks64();
    
    while (game.isRunning())
    {
        Uint64 frameStart = SDL_GetTicks64();
        
        float deltaTime = (frameStart - lastStart) / 1000.0f;
        lastStart = frameStart;

        InputManager::processEvents(&game);

        game.update(deltaTime);
        
        renderer.render(&game);

        // Limits to 60FPS
        Uint32 frameTime = SDL_GetTicks64() - frameStart;
        if (FRAME_DELAY > frameTime)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    renderer.quit();
    return 0;
}
