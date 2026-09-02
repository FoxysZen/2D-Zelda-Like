#pragma once
#include <SDL2/SDL_rect.h>

/**
 * @brief Manages the 2D viewport, converting world coordinates to screen space.
 */
class Camera
{
    public:
        Camera();
        ~Camera();

        /**
         * @brief Initilaizes the values of the camera.
         * 
         * @param width      The current width of the screen.
         * @param height     The current height of the screen.
         * @param _mapWidth  The width of the current map.
         * @param _mapHeight The height of the current map.
         */
        void init(int width, int height, int _mapWidth, int _mapHeight);
        /**
         * @brief Updates the camera to be centered in a position.
         * 
         * @param targetPos The current target to be centered.
         */
        void update(const SDL_Rect &targetPos);

        /**
         * @brief Centers the camera around a coordinate XY
         * 
         * @param coordX The coordinate X of the point.
         * @param coordY The coordinate Y of the point.
         * @param width  The width of the screen.
         * @param height The height of the screen.
         */
        void centerCamera(int coordX, int coordY);
        /**
         * @brief Sets the map bounds so that the camera does not go out of bounds.
         * 
         * @param _mapWidth  The width of the current map.
         * @param _mapHeight The height of the current map.
         */
        void setMapBounds(int _mapWidth, int _mapHeight);

        /**
         * @brief Gets the ViewPort parameters of the camera.
         * 
         * @return SDL_Rect with the parameters.
         */
        SDL_Rect getViewPort() const;

    private:
        /**
         * @brief Clamps the camera to the boundaries of the map.
         */
        void clampCamera();

        float camPosX = 0.0f;
        float camPosY = 0.0f;

        int screenWidth, screenHeight;
        int mapWidth, mapHeight;

        float smoothFactor = 0.1f;
};