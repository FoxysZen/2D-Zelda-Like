#include "Trigger.h"
#include <SDL2/SDL_rect.h>

TriggerZone::TriggerZone(uint8_t _tileId, const SDL_Rect &_position,
                         bool _enabled, const SDL_Rect &_area,
                         const SDL_Rect &_spawnPos, TriggerCallback _action, 
                         TriggerType _type, bool _oneShot, bool _isActive)
{
    tileId = _tileId;
    position = _position;
    enabled = _enabled;

    area = _area;
    spawnPos = _spawnPos;
    action = _action;
    type = _type;
    oneShot = _oneShot;
    isActive = _isActive;
}

TriggerZone::~TriggerZone() {}

void TriggerZone::checkColisions(const SDL_Rect &collider, 
                                 bool actionKeyPressed, bool isAttackCollider)
{
    if (!isActive || !enabled) return;

    bool colliding = SDL_HasIntersection(&collider, &area);

    if (isAttackCollider)
    {
        if (colliding && type == TriggerType::ON_ATTACK)
        {
            triggerAction();
        }
        return;
    }

    if (colliding && !isInside) // Enters
    {
        isInside = true;

        if (type == TriggerType::ON_ENTER)
        {
            triggerAction();
        }
    }
    else if (!colliding && isInside) // Exits
    {
        isInside = false;

        if (type == TriggerType::ON_EXIT)
        {
            triggerAction();
        }
    }
    else if (colliding && type == TriggerType::INTERACTIVE)
    {
        if (actionKeyPressed)
        {
            triggerAction();
        }
    }
}

void TriggerZone::triggerAction()
{
    if (action) action(this);

    if (oneShot)
    {
        isActive = false;
    }
}

const SDL_Rect *TriggerZone::getArea() const
{
    return &area;
}

uint8_t TriggerZone::getTileId() const
{
    return tileId;
}

const SDL_Rect *TriggerZone::getPosition() const
{
    return &position;
}

const SDL_Rect *TriggerZone::getSpawnPos() const
{
    return &spawnPos;
}

void TriggerZone::setTileId(uint8_t newTileId)
{
    tileId = newTileId;
}

void TriggerZone::setEnable(bool _enable)
{
    enabled = _enable;
}

bool TriggerZone::isEnabled() const
{
    return enabled;
}
