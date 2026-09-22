#include "Tilemap.h"

Tilemap::Tilemap() {}

Tilemap::~Tilemap() {}

void Tilemap::loadTileMap(const std::string &name)
{
    if (name == "test")
    {
        currentMap = LevelManager::getTestMap();
    }
    else
    {
        std::cerr << "Map: " << name << " does not exist." << std::endl;
    }
}

const MapData *Tilemap::getCurrentMap() const
{
    return &currentMap;
}

int Tilemap::getAnimationFrameIndex() const
{
    return animationFrame;
}

void Tilemap::updateSprites()
{
    ++animationFrame;

    int maxFrames = 4;

    if (animationFrame >= maxFrames)
    {
        animationFrame = 0;
    }
}
