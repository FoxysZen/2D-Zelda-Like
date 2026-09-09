#pragma once
#include <SDL2/SDL_rect.h>
#include <functional>

using TriggerCallback = std::function<void()>;

/**
 * @brief The way that the action will be triggered.
 */
enum TriggerType
{
    ON_ENTER,
    ON_EXIT,
    ON_ATTACK,
    INTERACTIVE
};

/**
 * @brief Detects entity overlap to trigger an event.
 */
class TriggerZone
{
    public:
        TriggerZone(const SDL_Rect& _area, TriggerCallback _action, 
                    TriggerType _type, bool _oneShot, bool _isActive);
        ~TriggerZone();

        /**
         * @brief Checks if the player has collided with the trigger.
         * 
         * @param collider The collider of the player.
         */
        void checkColisions(const SDL_Rect& collider, 
                            bool actionKeyPressed = true, 
                            bool isAttackCollider = false);

        /**
         * @brief Returns the area of the trigger.
         * 
         * @return Constant pointer to the SDL_Rect area.
         */
        const SDL_Rect *getArea() const;
    
    private:
        /**
         * @brief Triggers the function and checks oneShot.
         */
        void triggerAction();

        SDL_Rect area;
        TriggerCallback action;
        TriggerType type;
        bool oneShot, isActive;

        bool isInside;
};