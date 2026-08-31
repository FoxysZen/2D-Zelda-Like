#include "InputManager.h"
#include <SDL2/SDL_keycode.h>

void InputManager::processEvents(GameLogic *game)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            game->setRunning(false);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_UP:
                    game->moveUp();
                    break;
                case SDLK_DOWN:
                    game->moveDown();
                    break;
                case SDLK_LEFT:
                    game->moveLeft();
                    break;
                case SDLK_RIGHT:
                    game->moveRight();
                    break;
                case SDLK_w:
                    game->moveUp();
                    break;
                case SDLK_s:
                    game->moveDown();
                    break;
                case SDLK_a:
                    game->moveLeft();
                    break;
                case SDLK_d:
                    game->moveRight();
                    break;
                case SDLK_ESCAPE:
                    game->setRunning(false);
                    break;
            }
        }
    }
}
