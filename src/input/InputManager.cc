#include "InputManager.h"
#include "../core/GameLogic.h"

InputManager::InputManager()
{
    currentKeyboardState = SDL_GetKeyboardState(&numKeys);
    if (numKeys > 0)
    {
        previousKeyboardState.resize(numKeys, 0);
    }
}

InputManager::~InputManager() {}

void InputManager::processEvents(GameLogic *game)
{
    if (currentKeyboardState && !previousKeyboardState.empty()) 
    {
        std::memcpy(previousKeyboardState.data(), currentKeyboardState, numKeys);
    }

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

    currentKeyboardState = SDL_GetKeyboardState(NULL);

    float dirX = 0.0f;
    float dirY = 0.0f;

    if (isKeyDown(SDL_SCANCODE_W) || isKeyDown(SDL_SCANCODE_UP))
        dirY -= 1.0f;
    if (isKeyDown(SDL_SCANCODE_S) || isKeyDown(SDL_SCANCODE_DOWN))
        dirY += 1.0f;
    if (isKeyDown(SDL_SCANCODE_A) || isKeyDown(SDL_SCANCODE_LEFT))
        dirX -= 1.0f;
    if (isKeyDown(SDL_SCANCODE_D) || isKeyDown(SDL_SCANCODE_RIGHT))
        dirX += 1.0f;

    game->handlePlayerMovement(dirX, dirY);
}

bool InputManager::isKeyDown(SDL_Scancode scancode) const
{
    if (!currentKeyboardState)
        return false;
    return currentKeyboardState[scancode] != 0;
}

bool InputManager::isKeyPressed(SDL_Scancode scancode) const
{
    if (!currentKeyboardState || previousKeyboardState.empty())
        return false;
    return currentKeyboardState[scancode] && !previousKeyboardState[scancode];
}
