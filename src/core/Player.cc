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
        if (state != SWIMMING)
        {
            state = WALKING;
        }
    }
    else
    {
        state = IDLE;
        return;
    }

    float actualSpeed = speed;
    if (state == SWIMMING)
    {
        actualSpeed *= slowDown;
    }

    if (dirX != 0.0f)
    {
        rawPosX += dirX * actualSpeed * deltaTime + subX;
        position.x = static_cast<int>(std::round(rawPosX));
    }

    if (dirY != 0.0f)
    {
        rawPosY += dirY * actualSpeed * deltaTime + subY;
        position.y = static_cast<int>(std::round(rawPosY));
    }
}

void Player::updateSprite()
{
    ++animationFrame;

    int maxFrames = 1;
    
    if (state == PlayerStateMachine::WALKING)
    {
        maxFrames = WALK_FRAMES;
    }
    else if (state == PlayerStateMachine::IDLE)
    {
        maxFrames = IDLE_FRAMES;
    }

    if (animationFrame >= maxFrames)
    {
        animationFrame = 0;
    }
}

bool Player::isLookingLeft() const
{
    bool left = false;

    if (direction == Direction::LEFT)
    {
        left = true;
    }

    return left;
}

const SDL_Rect *Player::getPosition() const
{
    return &position;
}

const SDL_Rect *Player::getColision() const
{
    return &colision;
}

const SDL_Rect Player::getSpritePos() const
{
    SDL_Rect pos = {0, 0, 0, 0};
    int frames = 1;

    if (state == PlayerStateMachine::WALKING)
    {
        pos = PLAYER_WALK;
        frames = WALK_FRAMES;
    }
    else if (state == PlayerStateMachine::IDLE)
    {
        pos = PLAYER_IDLE;
        frames = IDLE_FRAMES;
    }

    if (direction == Direction::LEFT || direction == Direction::RIGHT)
    {
        pos.x += 1 * SPRITE_SIZE * frames;
    }
    else if (direction == Direction::BACK)
    {
        pos.x += 2 * SPRITE_SIZE * frames;
    }

    pos.x += animationFrame * SPRITE_SIZE;
    return pos;
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

void Player::setState(PlayerStateMachine newState)
{
    if (state != newState)
    {
        state = newState;
        animationFrame = 0;
    }
}

void Player::setDirection(Direction newDir)
{
    direction = newDir;
}
