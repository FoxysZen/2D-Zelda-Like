#pragma once
#include <cstddef>
#include "../core/GameLogic.h"
#include <iostream>
#include "LevelManager.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
//#include "../core/Tilemap.h"
#include <unordered_map>


const std::string playerAtlas = "../../assets/playerAtlas.png";

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
        SDL_Window *window;
        SDL_Renderer *renderer;

        int scale;

        std::unordered_map<std::string, SDL_Texture*> atlases;
};
