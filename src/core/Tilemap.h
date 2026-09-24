#pragma once
#include <cstdint>
#include <iostream>
#include "../graphics/LevelManager.h"
#include <string>
#include <vector>

/**
 * @brief Stores the map tiles in a matrix.
 */
class Tilemap
{
    public:
        Tilemap();
        ~Tilemap();

        /**
         * @brief Reads a tile map from the level manager.
         * 
         * @param name The name of the level.
         */
        void loadTileMap(const std::string &name);

        /**
         * @brief Gets the Wordl Map.
         * 
         * @return Pointer to the Matrix.
         */
        const MapData *getCurrentMap() const;
        /**
         * @brief Gets the index of the current animation frame.
         * 
         * @param True if its a 2 animation tile, false if its a 4 animation.
         * 
         * @return int
         */
        int getAnimationFrameIndex(bool single) const;

        /**
         * @brief Updates the animations of each tile that have it.
         */
        void updateSprites();

    private:
        MapData currentMap;

        int animationFrame = 0;
        int animationDoubleFrame = 0;
        const int maxFrames = 2;
};