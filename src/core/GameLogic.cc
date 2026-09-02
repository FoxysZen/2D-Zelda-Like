#include "GameLogic.h"
#include "Camera.h"

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

void GameLogic::moveUp()
{
    SDL_Rect pos = *player.getPosition();
    pos.y -= 4 * scale;
    player.setPosition(pos);
}

void GameLogic::moveDown()
{
    SDL_Rect pos = *player.getPosition();
    pos.y += 4 * scale;
    player.setPosition(pos);
}

void GameLogic::moveLeft()
{
    SDL_Rect pos = *player.getPosition();
    pos.x -= 4 * scale;
    player.setPosition(pos);
}

void GameLogic::moveRight()
{
    SDL_Rect pos = *player.getPosition();
    pos.x += 4 * scale;
    player.setPosition(pos);
}

void GameLogic::initPlayer()
{
    SDL_Rect sprite = {0, 32, 32, 32};

    player.init(sprite, {32 * scale, 32 * scale, 32, 32});
}
