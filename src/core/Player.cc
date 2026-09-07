#include "Player.h"

Player::Player() {}

Player::~Player() {}

int Player::init(const SDL_Rect &_spritePos, const SDL_Rect &_pos, 
                 const SDL_Rect &_col)
{
    spritePos = _spritePos;
    position = _pos;
    rawPosX = _pos.x;
    rawPosY = _pos.y;
    colision = _col;

    return 0;
}

void Player::move(float dirX, float dirY, float deltaTime)
{
    if (dirX != 0.0f || dirY != 0.0f)
    {
        state = WALKING;
    }
    else
    {
        state = IDLE;
        return;
    }

    if (dirX != 0.0f)
    {
        rawPosX += dirX * speed * deltaTime + subX;
        position.x = static_cast<int>(std::round(rawPosX));
    }

    if (dirY != 0.0f)
    {
        rawPosY += dirY * speed * deltaTime + subY;
        position.y = static_cast<int>(std::round(rawPosY));
    }
}

const SDL_Rect *Player::getPosition() const
{
    return &position;
}

const SDL_Rect *Player::getColision() const
{
    return &colision;
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
    rawPosX = static_cast<float>(newPos.x);
    rawPosY = static_cast<float>(newPos.y);
}

void Player::setPositionX(int _x)
{
    position.x = _x;
    rawPosX = static_cast<float>(_x);
}

void Player::setPositionY(int _y)
{
    position.y = _y;
    rawPosY = static_cast<float>(_y);
}
