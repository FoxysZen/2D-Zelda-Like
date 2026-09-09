#pragma once
#include <cstring>
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_scancode.h>
#include <string>
#include <vector>

/**
 * @brief Fordward declaration.
 */
class GameLogic;

/**
 * @brief Handles user inputs and triggers corresponding game actions.
 */
class InputManager
{
    public:
        InputManager();
        ~InputManager();
        /**
         * @brief Processes SDL events and updates the game state accordingly.
         * 
         * @param game Pointer to the GameLogic instance to update based on user input.
         */
        void processEvents(GameLogic *game);

        /**
         * @brief Checks if a key is down.
         * 
         * @param scancode The key to check.
         * @return true if the key is down, otherwise false.
         */
        bool isKeyDown(SDL_Scancode scancode) const;
        /**
         * @brief Checks if the kay was pressed on this frame.
         * 
         * @param scancode The key to check.
         * @return true if the key was pressed on this frame, otherwise false.
         */
        bool isKeyPressed(SDL_Scancode scancode) const;

    private:
        std::vector<Uint8> previousKeyboardState;
        const Uint8 *currentKeyboardState = nullptr;
        int numKeys = 0;
};
