#pragma once
#include <cstdint>

/**
 * @brief Handles all core game logic, state updates, and main loop flags.
 */
class GameLogic
{
    public:
        GameLogic();
        ~GameLogic();

        /**
         * @brief Updates the game state, entities, and logic for the current frame.
         */
        void update();

        /**
         * @brief Checks if the main loop is currently active.
         * 
         * @return True if the game is running, false if it should stop.
         */
        bool isRunning();
        /**
         * @brief Sets the game running status to control the main loop.
         * 
         * @param value True to keep the loop active, false to signal game exit.
         */
        void setRunning(bool value);

    private:
        bool running;
};
