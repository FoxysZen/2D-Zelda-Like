#include "Trigger.h"
#include <SDL2/SDL_rect.h>

TriggerZone::TriggerZone(const SDL_Rect& _area, TriggerCallback _action, 
                         TriggerType _type, bool _oneShot, bool _isActive)
{
    area = _area;
    action = _action;
    type = _type;
    oneShot = _oneShot;
    isActive = _isActive;
}

TriggerZone::~TriggerZone() {}

void TriggerZone::checkColisions(const SDL_Rect &collider, 
                                 bool actionKeyPressed, bool isAttackCollider)
{
    if (!isActive) return;

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
    if (action) action();

    if (oneShot)
    {
        isActive = false;
    }
}

const SDL_Rect *TriggerZone::getArea() const
{
    return &area;
}
