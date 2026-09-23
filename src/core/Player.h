#pragma once
#include <SDL2/SDL_rect.h>
#include <cstdint>
#include <string>

/**
 * @brief Indicates the direction the player is looking at.
 */
enum Direction
{
    FRONT,
    LEFT,
    RIGHT,
    BACK
};

/**
 * @brief Indicates the state of the player in the frame.
 */
enum PlayerStateMachine
{
    IDLE,
    WALKING,
    ATTACKING,
    SWIMMING
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
        int init(const SDL_Rect &_spritePos, const SDL_Rect &_pos, 
                 const SDL_Rect &_col);

        /**
         * @brief Moves the player in a certain direction.
         * 
         * @param dirX Horizontal amount.
         * @param dirY Vertical amount.
         * @param deltaTime Time between frames.
         */
        void move(float dirX, float dirY, float deltaTime);
        /**
         * @brief Updates the sprite of the animation.
         */
        void updateSprite();

        /**
         * @brief Returns if the player if looking at the left.
         * 
         * @return true if the direction of the player is Direction::LEFT, otherwise false.
         */
        bool isLookingLeft() const;
        /**
         * @brief Returns if the player is attacking.
         * 
         * @return true if PlayerStateMachine::ATTACKING.
         */
        bool isAttacking() const;

        /**
         * @brief Gets the current world position of the player.
         * 
         * @return The current SDL_Rect position.
         */
        const SDL_Rect *getPosition() const;
        /**
         * @brief Gets the Colision bounds of the player.
         * 
         * @return Constant pointer to the Rect
         */
        const SDL_Rect *getColision() const;
        /**
         * @brief Gets the SDL_Rect of the position of the sprite of the player.
         * 
         * @return The current SDL_Rect sprite.
         */
        const SDL_Rect getSpritePos() const;
        /**
         * @brief Gets the Atlas Name of the player.
         * 
         * @return Constant pointer to the std:string.
         */
        std::string getAtlasName() const;
        /**
         * @brief Get the Sword Hitbox
         * 
         * @return Constant SDL_Rect
         */
        const SDL_Rect getSwordHitbox() const;
        /**
         * @brief Gets the current animation rate for the player.
         * 
         * @return float 
         */
        float getAnimationRate() const;

        /**
         * @brief Sets the new world position of the player.
         * 
         * @param newPos The new SDL_Rect position of the player.
         */
        void setPosition(const SDL_Rect &newPos);
        /**
         * @brief Sets the new X world position of the player.
         * 
         * @param _x The X coordinate of the new position.
         */
        void setPositionX(int _x);
        /**
         * @brief Sets the new Y world position of the player.
         * 
         * @param _x The Y coordinate of the new position.
         */
        void setPositionY(int _y);
        /**
         * @brief Sets the State of the player
         * 
         * @param newDir The new State of the player.
         */
        void setState(PlayerStateMachine newState);
        /**
         * @brief Sets the Direction of the player
         * 
         * @param newDir The new direction where its looking at.
         */
        void setDirection(Direction newDir);

    private:
        SDL_Rect spritePos;
        SDL_Rect position = {32, 32, 32, 32};
        SDL_Rect colision = { 8, 24, 16,  8};
        int attackReach = 16;
        int attackThickness = 32;
        float rawPosX = 32.0f, rawPosY = 32.0f;
        float subX = 0.0f, subY = 0.0f;
        float speed = 90.0f; // px/s
        float slowDown = 0.75f;

        int animationFrame = 0;

        // Not const so so that the appearance can be changed in-game.
        std::string currentAtlas = "assets/playerAtlas.png";

        PlayerStateMachine state = IDLE;
        Direction direction = FRONT;

        const uint8_t SPRITE_SIZE = 32;

        const SDL_Rect PLAYER_IDLE = { 0, 32, 32, 32 };
        const SDL_Rect PLAYER_WALK = { 0, 64, 32, 32 };
        const SDL_Rect PLAYER_ATTACK = { 0, 96, 32, 32 };

        const uint8_t IDLE_FRAMES = 4;
        const uint8_t WALK_FRAMES = 4;
        const uint8_t ATTACK_FRAMES = 6;
};