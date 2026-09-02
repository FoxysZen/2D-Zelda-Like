#pragma once
#include <cstdint>
#include "Player.h"
#include "Tilemap.h"

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
         * @brief Initializes the Player object.
         */
        void initPlayer();

        /**
         * @brief Gets the pointer to the Player object.
         * 
         * @return Pointer to Player
         */
        Player *getPlayer();
        /**
         * @brief Gets the TileMap object
         * 
         * @return Tilemap* 
         */
        Tilemap *getTileMap();
        /**
         * @brief Checks if the main loop is currently active.
         * 
         * @return True if the game is running, false if it should stop.
         */
        bool isRunning() const;
        /**
         * @brief Sets the game running status to control the main loop.
         * 
         * @param value True to keep the loop active, false to signal game exit.
         */
        void setRunning(bool value);

        /**
         * @brief Moves the player 1 unit up.
         */
        void moveUp();
        /**
         * @brief Moves the player 1 unit down.
         */
        void moveDown();
        /**
         * @brief Moves the player 1 unit left.
         */
        void moveLeft();
        /**
         * @brief Moves the player 1 unit right.
         */
        void moveRight();

        int scale = 1;

    private:
        bool running;

        Player player;
        Tilemap tilemap;
};
