#pragma once
#include <algorithm>
#include <cstddef>
#include "../core/GameLogic.h"
#include <iostream>
#include "LevelManager.h"
#include <ostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

/**
 * @brief Handles window creation, SDL renderer setup, and drawing operations.
 */
class RenderEngine
{
    public:
        RenderEngine();
        ~RenderEngine();

        /**
         * @brief Initializes de RendererEngine and creates a window.
         * 
         * @param title The title of the window.
         * @param width Base width of the window in pixels.
         * @param height Base height of the window in pixels.
         * @param _scale Scale factor applied to width and height.
         * @return 0 if initialization succeeded, 1 if an SDL error occurred.
         */
        int init(const char *title, int width, int height, int _scale);
        /**
         * @brief Destroys the renderer, window, and cleans up SDL resources.
         */
        void quit();

        /**
         * @brief Loads a texture atlas and stores it in the vector of atlases.
         * 
         * @param texture The name of the texture atlas file.
         * @return 0 if loading succeeded, 1 if an SDL error occurred.
         */
        int loadTexture(const std::string &texture);

        /**
         * @brief Renders the current game state to the window.
         * 
         * @param game Pointer to the GameLogic object containing the state to draw.
         */
        void render(GameLogic *game);

    private:
        /**
         * @brief Draws the hitbox of a SDL_Rect with a specific colo.
         * 
         * @param worldHitbox The hitbox to be drawn.
         * @param camera      The Camera object.
         * @param color       A SDL_Color.
         */
        void drawHitbox(const SDL_Rect &worldHitbox, const Camera &camera, 
                        SDL_Color color) const;
        /**
         * @brief Checks if the tile is a 2 frame animation or a 4 one.
         * 
         * @param tileId The id of the tile to check.
         * @return True if the tile is 2 frame animation, otherwise false.
         */
        bool is2FrameAnimation(uint8_t tileId) const;
        /**
         * @brief Checks if the tile has animation.
         * 
         * @param tileId The id of the tile.
         * @return int 1 if has animation, otherwise 0.
         */
        int hasAnimation(uint8_t tileId) const;
        
        SDL_Window *window;
        SDL_Renderer *renderer;

        int scale;
        int screenWidth, screenHeight;

        std::unordered_map<std::string, SDL_Texture*> atlases;

        // Tile IDs
        // Water tile
        static constexpr uint8_t waterFull = 230;
        // Water inside
        static constexpr uint8_t waterInsideCornerUL = 224;
        static constexpr uint8_t waterInsideCornerDL = 240;
        static constexpr uint8_t waterInsideCornerUR = 226;
        static constexpr uint8_t waterInsideCornerDR = 242;
        // Water outside
        static constexpr uint8_t waterOutsideCornerUL = 212;
        static constexpr uint8_t waterOutsideCornerDL = 244;
        static constexpr uint8_t waterOutsideCornerUR = 216;
        static constexpr uint8_t waterOutsideCornerDR = 248;
        // Water sides
        static constexpr uint8_t waterSideU = 214;
        static constexpr uint8_t waterSideL = 228;
        static constexpr uint8_t waterSideR = 232;
        static constexpr uint8_t waterSideD = 246;

        // Flora
        static constexpr uint8_t blueFlower  = 6;
        static constexpr uint8_t whiteFlower = 22;
        static constexpr uint8_t redMushroom = 10;
};
