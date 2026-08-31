#include "GameLogic.h"

GameLogic::GameLogic()
{
    running = true;
}

GameLogic::~GameLogic() {}

void GameLogic::update()
{

}

bool GameLogic::isRunning()
{
    return running;
}

void GameLogic::setRunning(bool value)
{
    running = value;
}
