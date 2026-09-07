#include "GameLogic.h"

GameLogic::GameLogic()
{
    running = true;
}

GameLogic::~GameLogic() {}

void GameLogic::init(int _scale, int _screenWidth, int _screenHeight)
{
    scale = _scale;
    screenWidth  = _screenWidth;
    screenHeight = _screenHeight;

    tilemap.loadTileMap("test");
    initPlayer();
    const MapData *currentMap = tilemap.getCurrentMap();
    camera.init(
        screenWidth,
        screenHeight,
        currentMap->mapWidth * currentMap->tileSize,
        currentMap->mapHeight * currentMap->tileSize
    );
}

void GameLogic::update(const float &_deltaTime)
{
    deltaTime = _deltaTime;

    camera.update(*player.getPosition());
}

const Player *GameLogic::getPlayer()
{
    return &player;
}

const Tilemap *GameLogic::getTileMap()
{
    return &tilemap;
}

const Camera *GameLogic::getCamera()
{
    return &camera;
}

bool GameLogic::isRunning() const
{
    return running;
}

void GameLogic::setRunning(bool value)
{
    running = value;
}

void GameLogic::handlePlayerMovement(float dirX, float dirY)
{
    // Normalize
    if (dirX != 0.0f && dirY != 0.0f)
    {
        dirX *= 0.7071f;
        dirY *= 0.7071f;
    }

    if (dirX == 0.0f && dirY == 0.0f)
    {
        player.move(0.0f, 0.0f, deltaTime);
        return;
    }

    player.move(dirX, dirY, deltaTime);

    const SDL_Rect *colliderOffset = player.getColision();
    const SDL_Rect *playerPos = player.getPosition();

    SDL_Rect colX = {
        playerPos->x + colliderOffset->x,
        playerPos->y + colliderOffset->y,
        colliderOffset->w,
        colliderOffset->h
    };

    if (physics.checkMapColisions(colX, *tilemap.getCurrentMap(), Axis::X))
    {
        player.setPositionX(colX.x - colliderOffset->x);
    }

    playerPos = player.getPosition();
    SDL_Rect colY = {
        playerPos->x + colliderOffset->x,
        playerPos->y + colliderOffset->y,
        colliderOffset->w,
        colliderOffset->h
    };

    if (physics.checkMapColisions(colY, *tilemap.getCurrentMap(), Axis::Y))
    {
        player.setPositionY(colY.y - colliderOffset->y);
    }
}

void GameLogic::initPlayer()
{
    SDL_Rect sprite = {16, 0, 16, 16};

    player.init(sprite, {32 * scale, 32 * scale, 16, 16}, 
                {4, 12, 8, 4});
}
