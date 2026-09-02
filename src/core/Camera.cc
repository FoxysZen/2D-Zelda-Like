#include "Camera.h"

Camera::Camera() {}
Camera::~Camera() {}

void Camera::init(int width, int height, int _mapWidth, int _mapHeight)
{
    screenWidth  = width;
    screenHeight = height;

    mapWidth  = _mapWidth;
    mapHeight = _mapHeight;
}

void Camera::update(const SDL_Rect &targetPos)
{
    // Center of the target
    float centerX = targetPos.x + targetPos.w / 2.0f;
    // Adds a small offset to point slightly under the center
    float centerY = targetPos.y + targetPos.h / 2.0f + targetPos.h / 4.0f;
    
    float targetX = centerX - screenWidth / 2.0f;
    float targetY = centerY - screenHeight / 2.0f;

    // Lerp
    camPosX += (targetX - camPosX) * smoothFactor;
    camPosY += (targetY - camPosY) * smoothFactor;

    clampCamera();
}


void Camera::centerCamera(int coordX, int coordY)
{
    camPosX = coordX - screenWidth / 2.0f;
    camPosY = coordY - screenHeight / 2.0f;

    clampCamera();
}

void Camera::setMapBounds(int _mapWidth, int _mapHeight)
{
    mapWidth  = _mapWidth;
    mapHeight = _mapHeight;
}

SDL_Rect Camera::getViewPort() const
{
    SDL_Rect viewPort;

    viewPort.x = static_cast<int>(camPosX);
    viewPort.y = static_cast<int>(camPosY);
    viewPort.w = screenWidth;
    viewPort.h = screenHeight;

    return viewPort;
}

void Camera::clampCamera()
{
    if (camPosX < 0)
    {
        camPosX = 0;
    }
    if (camPosX > (mapWidth - screenWidth))
    {
        camPosX = mapWidth - screenWidth;
    }

    if (camPosY < 0)
    {
        camPosY = 0;
    }
    if (camPosY > (mapHeight - screenHeight))
    {
        camPosY = mapHeight - screenHeight;
    }
}
