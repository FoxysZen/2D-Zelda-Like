#pragma once
#include <SDL2/SDL_rect.h>
#include <cstdint>
#include <functional>

class TriggerZone; // Anticipated declaration

using TriggerCallback = std::function<void(TriggerZone*)>;

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
        TriggerZone(uint8_t _tileId, const SDL_Rect &_position, bool _enabled, 
                    const SDL_Rect &_area, const SDL_Rect &_spawnPos, 
                    TriggerCallback _action, TriggerType _type, bool _oneShot, 
                    bool _isActive);
        ~TriggerZone();

        /**
         * @brief Checks if the player has collided with the trigger.
         * 
         * @param collider The collider of the player.
         */
        void checkColisions(const SDL_Rect &collider, 
                            bool actionKeyPressed = true, 
                            bool isAttackCollider = false);

        /**
         * @brief Returns the area of the trigger.
         * 
         * @return Constant pointer to the SDL_Rect area.
         */
        const SDL_Rect *getArea() const;
        /**
         * @brief Gets the tileId.
         * 
         * @return uint8_t
         */
        uint8_t getTileId() const;
        /**
         * @brief Gets the position of the object.
         * 
         * @return const SDL_Rect*
         */
        const SDL_Rect *getPosition() const;
        /**
         * @brief Gets the Spawn Position of the warp.
         * 
         * @return const SDL_Rect* 
         */
        const SDL_Rect *getSpawnPos() const;
        /**
         * @brief Sets the new tileId.
         * 
         * @param newTileId The new id of the tile.
         */
        void setTileId(uint8_t newTileId);
        /**
         * @brief Changes the enabled variable.
         * 
         * @param _enable The new value of enable.
         */
        void setEnable(bool _enable);

        /**
         * @brief Checks if the object is enabled.
         * 
         * @return true if it is enabled, otherwise false.
         */
        bool isEnabled() const;
    
    private:
        /**
         * @brief Triggers the function and checks oneShot.
         */
        void triggerAction();

        // Object data
        uint8_t tileId = 0;
        SDL_Rect position { 0, 0, 0, 0 };
        bool enabled = true; // Object visibility
        
        // Trigger data
        SDL_Rect area;
        SDL_Rect spawnPos;
        TriggerCallback action;
        TriggerType type;
        bool oneShot, isActive; // Trigger active

        bool isInside;
};