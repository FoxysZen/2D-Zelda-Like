#include "core/GameLogic.h"
#include "graphics/RenderEngine.h"
#include "input/InputManager.h"
#include <SDL2/SDL.h>

const int SCALE = 4;
const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 144;

int main (int argc, char *argv[])
{
    RenderEngine renderer;
    renderer.init("2D Zelda Like", SCREEN_WIDTH, SCREEN_HEIGHT, SCALE);

    GameLogic game;
    game.scale = SCALE;
    game.initPlayer();

    renderer.loadTexture("assets/playerAtlas.png");
    
    while (game.isRunning())
    {
        InputManager::processEvents(&game);

        game.update();
        
        renderer.render(&game);

        // Limits to 60FPS
        SDL_Delay(16);
    }

    renderer.quit();
    return 0;
}
