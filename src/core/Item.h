#pragma once
#include <SDL2/SDL_rect.h>
#include <string>

class Item
{
    public:
        Item(SDL_Rect &_spritePos, SDL_Rect &_position, bool _visible, 
             bool _pickable);
        ~Item();
        
        /**
         * @brief Updates the animation and position of the item (if the item is in parabola).
         * 
         * @param deltaTime The deltaTime.
         */
        void updateItem(float deltaTime);
        /**
         * @brief Spawns the item on a position and launches the item up making a parabolic effect.
         * 
         * @param spawn_pos The starting position of the parabola.
         */
        void startParabolicSpawn(const SDL_Rect &spawn_pos);

        /**
         * @brief Gets the current sprite position.
         * 
         * @return const SDL_Rect with the current position of the sprite in the atlas.
         */
        const SDL_Rect getSpritePos() const;
        
        /**
         * @brief Sets the visibility of the item.
         * 
         * @param _visible The state of the new visibility.
         */
        void setVisibility(bool _visible);
        /**
         * @brief Sets the pickability of the item.
         * 
         * @param _pickable The state of the new pickability.
         */
        void setPickable(bool _pickable);

    private:
        
        /**
         * @brief Updates the sprite of the item.
         */
        void updateAnimation();

        // Graphics
        const std::string currentAtlas = "assets/itemAtlas.png";
        SDL_Rect spritePos = { 0, 0, 16, 16 };

        // Logic
        SDL_Rect position = { 32, 32, 16, 16 };
        SDL_Rect colision = {  0,  0, 16, 16 };
        float rawPosX = 32.0f, rawPosY = 32.0f;
        bool visible = true;
        bool pickable = true;

        bool inParabola = false;
        float timeInParabola = 0.0f;
        float parabolaTargetHeight;

        // Animation
        int animationFrame = 0;
        const uint8_t SPRITE_SIZE = 16;
        uint8_t IDLE_FRAMES = 4;
};
