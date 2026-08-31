#include "GameLogic.h"

GameLogic::GameLogic()
{
    running = true;
}

GameLogic::~GameLogic() {}

void GameLogic::update()
{

}

void GameLogic::initPlayer()
{
    SDL_Rect sprite = {0, 32, 32, 32};

    player.init(sprite, {50, 50, 32, 32});
}

Player *GameLogic::getPlayer()
{
    return &player;
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
    pos.y -= 32 * scale;
    player.setPosition(pos);
}

void GameLogic::moveDown()
{
    SDL_Rect pos = *player.getPosition();
    pos.y += 32 * scale;
    player.setPosition(pos);
}

void GameLogic::moveLeft()
{
    SDL_Rect pos = *player.getPosition();
    pos.x -= 32 * scale;
    player.setPosition(pos);
}

void GameLogic::moveRight()
{
    SDL_Rect pos = *player.getPosition();
    pos.x += 32 * scale;
    player.setPosition(pos);
}
