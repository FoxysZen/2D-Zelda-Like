#pragma once
#include <SDL2/SDL_rect.h>

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
         * @brief Sets the new world position of the player.
         * 
         * @param newPos The new SDL_Rect position of the player.
         */
        void setPosition(const SDL_Rect &newPos);

    private:
        SDL_Rect spritePos;
        SDL_Rect position;
};