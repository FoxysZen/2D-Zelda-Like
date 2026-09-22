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
         * @return int
         */
        int getAnimationFrameIndex() const;

        /**
         * @brief Updates the animations of each tile that have it.
         */
        void updateSprites();

    private:
        MapData currentMap;

        int animationFrame = 0;
};