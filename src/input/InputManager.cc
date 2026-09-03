#include "InputManager.h"

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
                case SDLK_ESCAPE:
                    game->setRunning(false);
                    break;
            }
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    float dirX = 0.0f;
    float dirY = 0.0f;

    if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])    dirY -= 1.0f;
    if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])  dirY += 1.0f;
    if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])  dirX -= 1.0f;
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) dirX += 1.0f;

    game->handlePlayerMovement(dirX, dirY);
}
