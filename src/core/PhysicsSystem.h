#pragma once
#include <algorithm>
#include "../graphics/LevelManager.h"
#include <SDL2/SDL_rect.h>

/**
 * @brief Represents an Axis.
 */
enum Axis
{
    X, Y
};

/**
 * @brief Detects and corrects all the colisions.
 */
class PhysicsSystem
{
    public:
        PhysicsSystem();
        ~PhysicsSystem();

        /**
         * @brief Checks the colision between the player and the map.
         * 
         * @param colA Collider of the player.
         * @param map  MapData with the data of the current map.
         * 
         * @return true If there was a collision, otherwise false.
         */
        bool checkMapColisions(SDL_Rect &colA, const MapData &map, Axis axis);

    private:
        /**
         * @brief Resolves the colision of a collider and a block.
         * 
         * @param colA     Collider of the object.
         * @param tileRect SDL_Rect of the block.
         * @param axis     Axis of correction.
         */
        void resolveBlockCollision(SDL_Rect &colA, const SDL_Rect &tileRect, 
                                   Axis axis);
        /**
         * @brief Resolves the colision of a collider and a slope.
         * 
         * @param colA      Collider of the object.
         * @param tileRect  SDL_Rect of the block.
         * @param slopeType Type of slope.
         * @param axis      Axis of correction.
         */
        void resolveSlopeCollision(SDL_Rect &colA, const SDL_Rect &tileRect, 
                                   uint8_t slopeType, Axis axis);
};