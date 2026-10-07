#include "Tilemap.h"

Tilemap::Tilemap() {}

Tilemap::~Tilemap() {}

void Tilemap::loadTileMap(const std::string &name)
{
    if (name == "test")
    {
        LevelManager::getTestMap(currentMap);
    }
    else if (name == "testSecret")
    {
        LevelManager::getTestSecretMap(currentMap);
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

MapData *Tilemap::getCurrentMapMutable()
{
    return &currentMap;
}

int Tilemap::getAnimationFrameIndex(bool single) const
{
    int frame = 0;

    if (single)
    {
        frame = animationFrame;
    }
    else
    {
        frame = animationDoubleFrame;
    }

    return frame;
}

void Tilemap::updateSprites()
{
    ++animationFrame;
    ++animationDoubleFrame;

    if (animationFrame >= maxFrames)
    {
        animationFrame = 0;
    }

    if (animationDoubleFrame >= (maxFrames * 2))
    {
        animationDoubleFrame = 0;
    }
}
