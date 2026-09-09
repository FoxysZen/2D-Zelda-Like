#include "GameLogic.h"
#include <SDL2/SDL_scancode.h>
#include <string>

GameLogic::GameLogic()
{
    running = true;
}

GameLogic::~GameLogic() {}

void GameLogic::init(int _scale, int _screenWidth, int _screenHeight, 
                     InputManager &_inputManager)
{
    scale = _scale;
    screenWidth  = _screenWidth;
    screenHeight = _screenHeight;
    input = &_inputManager;

    initPlayer();
    loadLevel("test");

    const MapData *currentMap = tilemap.getCurrentMap();
    camera.init(
        screenWidth,
        screenHeight,
        currentMap->mapWidth * currentMap->tileSize,
        currentMap->mapHeight * currentMap->tileSize
    );
}

void GameLogic::update(const float &_deltaTime)
{
    deltaTime = _deltaTime;

    checkTriggerCollisions();

    camera.update(*player.getPosition());
}

void GameLogic::loadLevel(const std::string &levelName)
{
    tilemap.loadTileMap(levelName);

    const MapData *map = tilemap.getCurrentMap();

    triggers.clear();
    triggerGrid.clear();
    triggerGrid.resize(map->mapWidth * map->mapHeight);

    size_t bushCount = 0;
    for (int tile : map->decorationMap)
    {
        if (tile == BUSH_TILE)
        {
            bushCount += 2;
        }
    }

    triggers.reserve(map->objectMap.size() + bushCount);

    for (const auto &data : map->objectMap)
    {
        triggers.push_back(createTriggerFromData(data));
    }

    int size = map->decorationMap.size();
    for (int i = 0; i < size; ++i)
    {
        if (map->decorationMap[i] == BUSH_TILE)
        {
            triggers.push_back(createBushTrigger(i, map->mapWidth,
                                                 map->tileSize, true));
            triggers.push_back(createBushTrigger(i, map->mapWidth,
                                                 map->tileSize, false));
        }
    }

    for (auto &trigger : triggers)
    {
        registerTriggerInGrid(&trigger);
    }
}

const Player *GameLogic::getPlayer()
{
    return &player;
}

const Tilemap *GameLogic::getTileMap()
{
    return &tilemap;
}

const Camera *GameLogic::getCamera()
{
    return &camera;
}

bool GameLogic::isRunning() const
{
    return running;
}

void GameLogic::setRunning(bool value)
{
    running = value;
}

void GameLogic::handlePlayerMovement(float dirX, float dirY)
{
    // Normalize
    if (dirX != 0.0f && dirY != 0.0f)
    {
        dirX *= 0.7071f;
        dirY *= 0.7071f;
    }

    if (dirX == 0.0f && dirY == 0.0f)
    {
        player.move(0.0f, 0.0f, deltaTime);
        return;
    }

    player.move(dirX, dirY, deltaTime);

    const SDL_Rect *colliderOffset = player.getColision();
    const SDL_Rect *playerPos = player.getPosition();

    SDL_Rect colX = {
        playerPos->x + colliderOffset->x,
        playerPos->y + colliderOffset->y,
        colliderOffset->w,
        colliderOffset->h
    };

    if (physics.checkMapColisions(colX, *tilemap.getCurrentMap(), Axis::X))
    {
        player.setPositionX(colX.x - colliderOffset->x);
    }

    playerPos = player.getPosition();
    SDL_Rect colY = {
        playerPos->x + colliderOffset->x,
        playerPos->y + colliderOffset->y,
        colliderOffset->w,
        colliderOffset->h
    };

    if (physics.checkMapColisions(colY, *tilemap.getCurrentMap(), Axis::Y))
    {
        player.setPositionY(colY.y - colliderOffset->y);
    }
}

void GameLogic::initPlayer()
{
    SDL_Rect sprite = {16, 0, 16, 16};

    player.init(sprite, {32, 32, 16, 16}, {4, 12, 8, 4});
}

void GameLogic::registerTriggerInGrid(TriggerZone *trigger)
{
    const SDL_Rect *area = trigger->getArea();

    const int tileSize = tilemap.getCurrentMap()->tileSize;
    const int mapWidth  = tilemap.getCurrentMap()->mapWidth;
    const int mapHeight = tilemap.getCurrentMap()->mapHeight;

    int startX = std::max(0, area->x / tileSize);
    int startY = std::max(0, area->y / tileSize);
    int endX   = std::min(mapWidth - 1,  (area->x + area->w - 1) / tileSize);
    int endY   = std::min(mapHeight - 1, (area->y + area->h - 1) / tileSize);

    for (int y = startY; y <= endY; ++y) 
    {
        for (int x = startX; x <= endX; ++x) 
        {
            int index = y * mapWidth + x;
            triggerGrid[index].push_back(trigger);
        }
    }
}

void GameLogic::checkTriggerCollisions()
{
    const SDL_Rect *colOffset = player.getColision();
    const SDL_Rect *playerPos = player.getPosition();

    SDL_Rect playerWorldHitbox = {
        playerPos->x + colOffset->x,
        playerPos->y + colOffset->y,
        colOffset->w,
        colOffset->h
    };

    const int tileSize  = tilemap.getCurrentMap()->tileSize;
    const int mapWidth  = tilemap.getCurrentMap()->mapWidth;
    const int mapHeight = tilemap.getCurrentMap()->mapHeight;

    int startX = std::max(0, playerWorldHitbox.x / tileSize);
    int startY = std::max(0, playerWorldHitbox.y / tileSize);
    int endX = std::min(mapWidth - 1, 
                        (playerWorldHitbox.x + playerWorldHitbox.w - 1) / tileSize);
    int endY = std::min(mapHeight - 1, 
                        (playerWorldHitbox.y + playerWorldHitbox.h - 1) / tileSize);

    bool actionPressed = checkKeyPressed("action");
    //bool attackPressed = checkKeyPressed("attack");

    std::unordered_set<TriggerZone*> checkedTriggers;

    for (int y = startY; y <= endY; ++y) 
    {
        for (int x = startX; x <= endX; ++x) 
        {
            int index = y * mapWidth + x;

            for (TriggerZone *trigger : triggerGrid[index]) 
            {
                if (checkedTriggers.insert(trigger).second) 
                {
                    trigger->checkColisions(playerWorldHitbox, actionPressed, 
                                            false);
                }
            }
        }
    }

    //if (attackPressed)
    //{
    //    SDL_Rect swordHitbox = player.getSwordHitbox(); 
//
    //    int sStartX = std::max(0, swordHitbox.x / tileSize);
    //    int sStartY = std::max(0, swordHitbox.y / tileSize);
    //    int sEndX   = std::min(mapWidth - 1, 
    //                           (swordHitbox.x + swordHitbox.w - 1) / tileSize);
    //    int sEndY   = std::min(mapHeight - 1, 
    //                           (swordHitbox.y + swordHitbox.h - 1) / tileSize);
//
    //    for (int y = sStartY; y <= sEndY; ++y) 
    //    {
    //        for (int x = sStartX; x <= sEndX; ++x) 
    //        {
    //            int index = y * mapWidth + x;
    //            for (TriggerZone *trigger : triggerGrid[index]) 
    //            {
    //                if (checkedTriggers.insert(trigger).second) 
    //                {
    //                    trigger->checkColisions(swordHitbox, false, true);
    //                }
    //            }
    //        }
    //    }
    //}
}

bool GameLogic::checkKeyPressed(const std::string &action)
{
    bool isPressed = false;

    if (action == "action" && input->isKeyPressed(SDL_SCANCODE_E))
    {
        isPressed = true;
    }
    else if (action == "attack" && input->isKeyPressed(SDL_SCANCODE_SPACE))
    {
        isPressed = true;
    }

    return isPressed;
}

TriggerZone GameLogic::createTriggerFromData(const ObjectData &data)
{
    TriggerCallback action = nullptr;

    switch (data.trigger.event)
    {
        case TriggerEvent::CHANGE_MAP:
            action = [this, data]() {
                this->loadLevel(data.trigger.map);
            };
            break;
        //case TriggerEvent::MSG_SIGN:
        case TriggerEvent::MSG_NPC:
            action = [this, data]() {
                showMessage(data.trigger.msg);
            };
            break;
        //case TriggerEvent::TAKE_DMG:
        //    action = [this, data]() {
        //        this->player.takeDamage(data.trigger.amount);
        //    };
        //    break;
        //case TriggerEvent::HEAL:
        //    action = [this, data]() {
        //        this->player.heal(data.trigger.amount);
        //    };
        //    break;
        case TriggerEvent::NONE:
        default:
            action = nullptr;
            break;
    }

    SDL_Rect position = data.position;
    position.x += data.trigger.area.x;
    position.y += data.trigger.area.y;
    position.w  = data.trigger.area.w;
    position.h  = data.trigger.area.h;

    return TriggerZone(
        position,
        action,
        data.trigger.type,
        data.trigger.oneShot,
        data.trigger.isActive
    );
}

TriggerZone GameLogic::createBushTrigger(int i, int width, int tileSize,
                                         bool oneShot)
{
    int x = (i % width) * tileSize;
    int y = (i / width) * tileSize;

    TriggerType type = TriggerType::ON_ENTER;
    TriggerCallback action = nullptr;
    if (oneShot)
    {
        type = TriggerType::ON_ATTACK;
        //action = []() {
        //    drawParticle(...);
        //};
    }
    else
    {
        action = [this]() {
            showMessage("Bush particle!");
        };
    }

    int margin = 2;
    return TriggerZone(
        {
            x + margin,
            y + margin,
            tileSize - (margin * 2),
            tileSize - (margin * 2)
        },
        action,
        type,
        oneShot,
        true
    );
}

void GameLogic::showMessage(const std::string &msg)
{
    std::cout << msg << std::endl;
}
