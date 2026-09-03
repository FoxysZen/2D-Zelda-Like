#include "Player.h"

Player::Player() {}

Player::~Player() {}

int Player::init(const SDL_Rect &_spritePos, const SDL_Rect &_pos)
{
    spritePos = _spritePos;
    position = _pos;
    rawPosX = _pos.x;
    rawPosY = _pos.y;

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

    if (dirX != 0.0f && dirY != 0.0f)
    {
        dirX *= 0.7071f; // 1 / sqrt(2)
        dirY *= 0.7071f;
    }

    rawPosX += dirX * speed * deltaTime;
    rawPosY += dirY * speed * deltaTime;

    position.x = static_cast<int>(rawPosX);
    position.y = static_cast<int>(rawPosY);
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
