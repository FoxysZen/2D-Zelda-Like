#include "Player.h"

Player::Player()
{

}

Player::~Player() {}

int Player::init(const SDL_Rect &_spritePos, const SDL_Rect &_pos)
{
    spritePos = _spritePos;
    position = _pos;

    return 0;
}

const SDL_Rect *Player::getPosition() const
{
    return &position;
}

const SDL_Rect *Player::getSpritePos() const
{
    return &spritePos;
}

std::string Player::getAtlasName() const
{
    return currentAtlas;
}

void Player::setPosition(const SDL_Rect &newPos)
{
    position = newPos;
}
