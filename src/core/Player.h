#pragma once
#include <SDL2/SDL_rect.h>
#include <string>

enum playerStateMachine
{
    IDLE,
    WALKING,
    ATTACKING
};

/**
 * @brief Handles the player's state, position, and sprite data.
 */
class Player
{
    public:
        Player();
        ~Player();

        /**
         * @brief Initializes the player's initial position and sprite coordinates.
         * 
         * @param _sprite The rectangle in the sprite atlas.
         * @param _pos The spawn position in world space.
         * @return 0 if no errors occur, otherwise 1.
         */
        int init(const SDL_Rect &_spritePos, const SDL_Rect &_pos);

        /**
         * @brief Moves the player in a certain direction.
         * 
         * @param dirX Horizontal amount.
         * @param dirY Vertical amount.
         * @param deltaTime Time between frames.
         */
        void move(float dirX, float dirY, float deltaTime);

        /**
         * @brief Gets the current world position of the player.
         * 
         * @return The current SDL_Rect position.
         */
        const SDL_Rect *getPosition() const;
        /**
         * @brief Gets the SDL_Rect of the position of the sprite of the player.
         * 
         * @return The current SDL_Rect sprite.
         */
        const SDL_Rect *getSpritePos() const;
        /**
         * @brief Gets the Atlas Name of the player.
         * 
         * @return Constant pointer to the std:string.
         */
        std::string getAtlasName() const;

        /**
         * @brief Sets the new world position of the player.
         * 
         * @param newPos The new SDL_Rect position of the player.
         */
        void setPosition(const SDL_Rect &newPos);

    private:
        SDL_Rect spritePos;
        SDL_Rect position = {32, 32, 16, 16};
        float rawPosX = 32.0f, rawPosY = 32.0f;
        float speed = 120.0f; // px/s

        // Not const so so that the appearance can be changed in-game.
        std::string currentAtlas = "assets/playerAtlas.png";

        playerStateMachine state = IDLE;
};