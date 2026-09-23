#pragma once
#include "Camera.h"
#include <cstdint>
#include <functional>
#include "../input/InputManager.h"
#include <iostream>
#include "PhysicsSystem.h"
#include "Player.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <string>
#include "Tilemap.h"
#include "Trigger.h"
#include <unordered_set>
#include <vector>

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
        void init(int _scale, int _screenWidth, int _screenHeight, 
                  InputManager &_inputManager);
        /**
         * @brief Updates the game state, entities, and logic for the current frame.
         * 
         * @param _deltaTime The time between frames.
         */
        void update(const float &_deltaTime);
        /**
         * @brief Calculates when the animations have to change sprite.
         */
        void updateAnimations();
        /**
         * @brief Loads a level by the name.
         * 
         * @param levelName The name of the level
         */
        void loadLevel(const std::string &levelName);
        /**
         * @brief Sets the player state in PlayerStateMachine::ATTACKING
         */
        void startAttack();

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
         * @brief Checks if the game is in debug mode.
         * 
         * @return True if debugMode is true.
         */
        bool isInDebugMode() const;
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
        /**
         * @brief Stores the trigger in the triggerGrid.
         * 
         * @param trigger The pointer to the trigger to be stored.
         */
        void registerTriggerInGrid(TriggerZone *trigger);
        /**
         * @brief Checks if the player has triggered any collider.
         */
        void checkTriggerCollisions();
        /**
         * @brief Checks if an action key is being pressed.
         * 
         * @param action The name of the action.
         * @return true if the key/s are pressed, otherwise false.
         */
        bool checkKeyPressed(const std::string &action);
        /**
         * @brief Creates a trigger from objectData.
         * 
         * @param data The objectData with the trigger information.
         * @return TriggerZone
         */
        TriggerZone createTriggerFromData(const ObjectData &data);
        /**
         * @brief Creates 2 triggers. One for the particles and one for attack.
         * 
         * @param i      The position of the bush in the vector.
         * @param width  The width of the map.
         * @param height The height of the map.
         * @return TriggerZone 
         */
        TriggerZone createBushTrigger(int i, int width, int tileSize,
                                      bool oneShot);

        /**
         * @brief Test action that prints a msg in the terminal.
         * 
         * @param msg The message that will be shown in the terminal.
         */
        void showMessage(const std::string &msg);

        bool running;
        bool debugMode = false;
        int scale = 1;
        float deltaTime;

        int screenWidth, screenHeight;

        Camera camera;
        PhysicsSystem physics;
        Player player;
        Tilemap tilemap;
        InputManager *input;

        // Animations
        float bgRateAnimation = 0.2f;
        float playerRateAnimation = 0.125f;
        float bgTimer = 0.0f;
        float playerTimer = 0.0f;

        std::vector<TriggerZone> triggers;
        std::vector<std::vector<TriggerZone*>> triggerGrid;

        // Trigger tiles
        const uint8_t BUSH_TILE = 40;
};
