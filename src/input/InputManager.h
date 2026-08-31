#pragma once
#include "../core/GameLogic.h"
#include <SDL2/SDL.h>

/**
 * @brief Handles user inputs and triggers corresponding game actions.
 */
class InputManager
{
    public:
        /**
         * @brief Processes SDL events and updates the game state accordingly.
         * 
         * @param game Pointer to the GameLogic instance to update based on user input.
         */
        static void processEvents(GameLogic *game);
};
