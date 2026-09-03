#pragma once
#include "Camera.h"
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
         * @brief Initializes the tilemap, player and the camera, aswell as the variables.
         */
        void init(int _scale, int _screenWidth, int _screenHeight);
        /**
         * @brief Updates the game state, entities, and logic for the current frame.
         */
        void update(const float &_deltaTime);

        /**
         * @brief Gets the pointer to the Player object.
         * 
         * @return constant pointer to the Player.
         */
        const Player *getPlayer();
        /**
         * @brief Gets the TileMap object.
         * 
         * @return Constant pointer to the Tilemap.
         */
        const Tilemap *getTileMap();
        /**
         * @brief Gets the Camera object.
         * 
         * @return Constant pointer to the Camera.
         */
        const Camera *getCamera();

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
         * @brief Moves the player in the direction passed.
         * 
         * @param dirX Horizontal movement.
         * @param dirY Vertical movement.
         */
        void handlePlayerMovement(float dirX, float dirY);

    private:
        /**
         * @brief Initializes the Player object.
         */
        void initPlayer();

        bool running;
        int scale = 1;
        float deltaTime;

        int screenWidth, screenHeight;

        Camera camera;
        Player player;
        Tilemap tilemap;
};
