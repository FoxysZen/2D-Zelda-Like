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
        if (state != PlayerStateMachine::SWIMMING)
        {
            setState(PlayerStateMachine::WALKING);;
        }
    }
    else
    {
        setState(PlayerStateMachine::IDLE);
        return;
    }

    float actualSpeed = speed;
    if (state == PlayerStateMachine::SWIMMING)
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
    else if (state == PlayerStateMachine::ATTACKING)
    {
        // +1 for isAttacking() so that it can enter the if
        maxFrames = ATTACK_FRAMES + 1;
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

bool Player::isAttacking() const
{
    bool attacking = false;

    if (state == PlayerStateMachine::ATTACKING && animationFrame < ATTACK_FRAMES)
    {
        attacking = true;
    }

    return attacking;
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
    else if (state == PlayerStateMachine::ATTACKING)
    {
        pos = PLAYER_ATTACK;
        frames = ATTACK_FRAMES;
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

const SDL_Rect Player::getSwordHitbox() const
{
    SDL_Rect swordHitbox;

    const int footCenterX = 16; // 8 + 16/2 (colision x)
    const int footCenterY = 28; // 24 + 8/2 (colision y)

    switch (direction)
    {
        case Direction::FRONT:
            swordHitbox.x = footCenterX - (attackThickness / 2);
            swordHitbox.y = footCenterY;
            swordHitbox.w = attackThickness;
            swordHitbox.h = attackReach;
            break;

        case Direction::BACK:
            swordHitbox.x = footCenterX - (attackThickness / 2);
            swordHitbox.y = footCenterY - attackReach;
            swordHitbox.w = attackThickness;
            swordHitbox.h = attackReach;
            break;

        case Direction::LEFT:
            swordHitbox.x = footCenterX - attackReach;
            swordHitbox.y = footCenterY - (attackThickness / 2);
            swordHitbox.w = attackReach;
            swordHitbox.h = attackThickness;
            break;

        case Direction::RIGHT:
            swordHitbox.x = footCenterX;
            swordHitbox.y = footCenterY - (attackThickness / 2);
            swordHitbox.w = attackReach;
            swordHitbox.h = attackThickness;
            break;
    }

    return swordHitbox;
}

float Player::getAnimationRate() const
{
    float rate = 0.125f;

    switch (state)
    {
        case PlayerStateMachine::IDLE:
            rate = 0.125f;
            break;
        case PlayerStateMachine::WALKING:
            rate = 0.125f;
            break;
        case PlayerStateMachine::ATTACKING:
            rate = 0.035f;
            break;
        default:
            rate = 0.125f;
            break;
    }

    return rate;
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
        // No state change while attacking (Except death).
        if (isAttacking())
        {
            return;
        }

        state = newState;
        animationFrame = 0;
    }
}

void Player::setDirection(Direction newDir)
{
    direction = newDir;
}
