#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem() {}
PhysicsSystem::~PhysicsSystem() {}

bool PhysicsSystem::checkMapColisions(SDL_Rect &colA, const MapData &map, 
                                      Axis axis)
{
    const int tileSize = map.tileSize;

    int startGridX = 
        static_cast<int>(std::floor(static_cast<float>(colA.x) / tileSize));
    int startGridY = 
        static_cast<int>(std::floor(static_cast<float>(colA.y) / tileSize));

    int endGridX = 
        static_cast<int>(std::floor(static_cast<float>(colA.x + colA.w - 1)
                                                      / tileSize));
    int endGridY = 
        static_cast<int>(std::floor(static_cast<float>(colA.y + colA.h - 1)
                                                      / tileSize));

    // AABB
    bool collision = false;
    for (int i = startGridX; i <= endGridX; ++i)
    {
        if (i < 0 || i >= map.mapWidth)
                continue;
        
        for (int j = startGridY; j <= endGridY; ++j)
        {
            if (j < 0 || j >= map.mapHeight)
                continue;

            uint8_t tile = map.colisionMap[j * map.mapWidth + i];

            if (tile == 0) // No colision
                continue;

            SDL_Rect tileRect = {
                i * tileSize,
                j * tileSize,
                tileSize,
                tileSize
            };

            if (tile == 1) // Block
            {
                resolveBlockCollision(colA, tileRect, axis);
                collision = true;
            }
            else if (tile >= 2 && tile <= 5) // Slope
            {
                resolveSlopeCollision(colA, tileRect, tile, axis);
                collision = true;
            }
        }
    }

    return collision;
}

void PhysicsSystem::resolveBlockCollision(SDL_Rect &colA, 
                                          const SDL_Rect &tileRect, Axis axis)
{
    //SDL_Rect intersection;
    //
    //if (!SDL_IntersectRect(&colA, &tileRect, &intersection))
    //    return;
//
    //if (axis == Axis::X)
    //{
    //    if (colA.x  < tileRect.x)
    //    {
    //        colA.x -= intersection.w;
    //    }
    //    else
    //    {
    //        colA.x += intersection.w;
    //    }
    //}
    //else if (axis == Axis::Y)
    //{
    //    if (colA.y < tileRect.y)
    //    {
    //        colA.y -= intersection.h;
    //    }
    //    else
    //    {
    //        colA.y += intersection.h;
    //    }
    //}

    SDL_Rect intersection;
    
    if (!SDL_IntersectRect(&colA, &tileRect, &intersection))
        return;

    if (axis == Axis::X)
    {
        if (intersection.h < intersection.w)
        {
            return;
        }

        if (colA.x < tileRect.x)
        {
            colA.x -= intersection.w;
        }
        else
        {
            colA.x += intersection.w;
        }
    }
    else if (axis == Axis::Y)
    {
        if (intersection.w < intersection.h)
        {
            return;
        }

        if (colA.y < tileRect.y)
        {
            colA.y -= intersection.h;
        }
        else
        {
            colA.y += intersection.h;
        }
    }
}

void PhysicsSystem::resolveSlopeCollision(SDL_Rect &colA, 
                                          const SDL_Rect &tileRect, 
                                          uint8_t slopeType, Axis axis)
{
    SDL_Rect intersection;
    if (!SDL_IntersectRect(&colA, &tileRect, &intersection))
        return;

    const float tileSize = static_cast<float>(tileRect.w);

    if (axis == Axis::Y)
    {
        if (slopeType == 2)
        {
            float playerLocalX = static_cast<float>(colA.x - tileRect.x);
            playerLocalX = std::clamp(playerLocalX, 0.0f, tileSize);

            float solidMaxY = tileRect.y + (tileSize - playerLocalX);

            if (colA.y < solidMaxY)
            {
                colA.y = static_cast<int>(solidMaxY);
            }
        }
        else if (slopeType == 3)
        {
            float playerLocalX = static_cast<float>((colA.x + colA.w) - tileRect.x);
            playerLocalX = std::clamp(playerLocalX, 0.0f, tileSize);

            float solidMaxY = tileRect.y + playerLocalX;

            if (colA.y < solidMaxY)
            {
                colA.y = static_cast<int>(solidMaxY);
            }
        }
        else if (slopeType == 4)
        {
            float playerLocalX = static_cast<float>(colA.x - tileRect.x);
            playerLocalX = std::clamp(playerLocalX, 0.0f, tileSize);

            float solidMinY = tileRect.y + playerLocalX;

            if ((colA.y + colA.h) > solidMinY)
            {
                colA.y = static_cast<int>(solidMinY - colA.h);
            }
        }
        else if (slopeType == 5)
        {
            float playerLocalX = static_cast<float>((colA.x + colA.w) - tileRect.x);
            playerLocalX = std::clamp(playerLocalX, 0.0f, tileSize);

            float solidMinY = tileRect.y + (tileSize - playerLocalX);

            if ((colA.y + colA.h) > solidMinY)
            {
                colA.y = static_cast<int>(solidMinY - colA.h);
            }
        }
    }
    else if (axis == Axis::X)
    {
        if (slopeType == 2)
        {
            float playerLocalY = static_cast<float>(colA.y - tileRect.y);
            playerLocalY = std::clamp(playerLocalY, 0.0f, tileSize);

            float solidMaxX = tileRect.x + (tileSize - playerLocalY);

            if (colA.x < solidMaxX)
            {
                colA.x = static_cast<int>(solidMaxX);
            }
        }
        else if (slopeType == 3)
        {
            float playerLocalY = static_cast<float>(colA.y - tileRect.y);
            playerLocalY = std::clamp(playerLocalY, 0.0f, tileSize);

            float solidMinX = tileRect.x + playerLocalY;

            if ((colA.x + colA.w) > solidMinX)
            {
                colA.x = static_cast<int>(solidMinX - colA.w);
            }
        }
        else if (slopeType == 4)
        {
            float playerLocalY = static_cast<float>((colA.y + colA.h) - tileRect.y);
            playerLocalY = std::clamp(playerLocalY, 0.0f, tileSize);

            float solidMaxX = tileRect.x + playerLocalY;

            if (colA.x < solidMaxX)
            {
                colA.x = static_cast<int>(solidMaxX);
            }
        }
        else if (slopeType == 5)
        {
            float playerLocalY = static_cast<float>((colA.y + colA.h) - tileRect.y);
            playerLocalY = std::clamp(playerLocalY, 0.0f, tileSize);

            float solidMinX = tileRect.x + (tileSize - playerLocalY);

            if ((colA.x + colA.w) > solidMinX)
            {
                colA.x = static_cast<int>(solidMinX - colA.w);
            }
        }
    }
}
