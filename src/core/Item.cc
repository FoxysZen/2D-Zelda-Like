#include "Item.h"

Item::Item(SDL_Rect &_spritePos, SDL_Rect &_position, bool _visible, 
     bool _pickable)
{
    spritePos = _spritePos;
    position = _position;
    visible = _visible;
    pickable = _pickable;
}

Item::~Item() {}

void Item::updateItem(float deltaTime)
{
    if (inParabola)
    {
        // Update position

        timeInParabola += deltaTime;
        if (position.y >= parabolaTargetHeight)
        {
            timeInParabola = 0.0f;
            inParabola = false;
            pickable = true;
        }
    }
    else
    {
        // Make the item floating up and down some pixels
    }
}

void Item::startParabolicSpawn(const SDL_Rect &spawn_pos)
{
    parabolaTargetHeight = spawn_pos.y;
    position = spawn_pos;
    visible = true;
    pickable = false;
    inParabola = true;
    timeInParabola = 0.0f;
}

const SDL_Rect Item::getSpritePos() const
{
    SDL_Rect pos = spritePos;
    pos.x += animationFrame * SPRITE_SIZE;

    return pos;
}

void Item::setVisibility(bool _visible)
{
    visible = _visible;
}

void Item::setPickable(bool _pickable)
{
    pickable = _pickable;
}

void Item::updateAnimation()
{
    ++animationFrame;

    if (animationFrame >= IDLE_FRAMES)
    {
        animationFrame = 0;
    }
}
