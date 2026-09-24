#include "RenderEngine.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <ostream>
#include <utility>

RenderEngine::RenderEngine() {}
RenderEngine::~RenderEngine() {}

int RenderEngine::init(const char *title, int width, int height, int _scale)
{
    scale        = _scale;
    screenWidth  = width;
    screenHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL2: " << SDL_GetError() << std::endl;
        return 1;
    }

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width * scale,
        height * scale,
        SDL_WINDOW_SHOWN
    );
    if (!window)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Surface* icon = IMG_Load("assets/icon.png");
    if (icon != nullptr) 
    {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    } 
    else 
    {
        std::cerr << "Warning: Could not load window icon: " << IMG_GetError()
            << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
}

void RenderEngine::quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int RenderEngine::loadTexture(const std::string &texture)
{
    SDL_Texture* atlas = IMG_LoadTexture(renderer, texture.c_str());
    if (!atlas)
    {
        std::cerr << "Error loading texture '" << texture << "': " 
            << SDL_GetError() << std::endl;
        return 1;
    }
    atlases[texture] = atlas;

    return 0;
}

void RenderEngine::render(GameLogic *game)
{
    // BG color fill
    SDL_SetRenderDrawColor(renderer, 155, 188, 15, 255);
    SDL_RenderClear(renderer);

    const MapData *map = game->getTileMap()->getCurrentMap();
    const int mapWidth = map->mapWidth;
    const int mapHeight = map->mapHeight;
    const int tileSize = map->tileSize;
    const std::string mapAtlas = map->atlas;

    // Camera Bounds for Tile Culling
    SDL_Rect viewPort = game->getCamera()->getViewPort();
    int startX = viewPort.x / tileSize;
    int startY = viewPort.y / tileSize;
    int endX   = (viewPort.x + viewPort.w) / tileSize + 2;
    int endY   = (viewPort.y + viewPort.h) / tileSize + 2;

    startX = std::max(0, startX);
    startY = std::max(0, startY);
    endX   = std::min(mapWidth, endX);
    endY   = std::min(mapHeight, endY);

    int atlasWidth;
    SDL_QueryTexture(
        atlases[mapAtlas],
        nullptr,
        nullptr,
        &atlasWidth,
        nullptr
    );
    const int tilesPerRow = atlasWidth / tileSize;

    // Map
    for (int y = startY; y < endY; ++y)
    {
        for (int x = startX; x < endX; ++x)
        {
            // Base Tiles
            uint8_t tileId = map->worldMap[y * mapWidth + x];

            int animate = hasAnimation(tileId);

            int animationFrame = 
                game->getTileMap()->getAnimationFrameIndex(is2FrameAnimation(tileId));
            
            // Tile position in the PNG
            int i = (tileId + animationFrame * animate) % tilesPerRow * tileSize;
            int j = (tileId + animationFrame * animate) / tilesPerRow * tileSize;
            SDL_Rect tileTexture = {i, j, tileSize, tileSize};

            // Tile position in the world space.
            int posX = x * tileSize;
            int posY = y * tileSize;
            SDL_Rect tilePos = {
                (posX - viewPort.x) * scale,
                (posY - viewPort.y) * scale,
                tileSize * scale,
                tileSize * scale
            };

            SDL_RenderCopy(renderer, atlases[mapAtlas], &tileTexture, &tilePos);

            // Decoration Tiles
            tileId = map->decorationMap[y * mapWidth + x];
            if (tileId != 0)
            {
                // Tile position in the PNG
                i = (tileId + animationFrame * animate) % tilesPerRow * tileSize;
                j = (tileId + animationFrame * animate) / tilesPerRow * tileSize;
                tileTexture  = {i, j, tileSize, tileSize};
                
                // Tile position in the world space can be reutilized.
                
                SDL_RenderCopy(renderer, atlases[mapAtlas], &tileTexture, &tilePos);
            }
        }
    }

    // Render Objects
    for (const auto &data : map->objectMap)
    {
        int animate = hasAnimation(data.tileId);

        int animationFrame = 
            game->getTileMap()->getAnimationFrameIndex(is2FrameAnimation(data.tileId));

        // Tile position in the PNG
        SDL_Rect tileTexture = {
            (data.tileId + animationFrame * animate) % tilesPerRow * tileSize,
            (data.tileId + animationFrame * animate) / tilesPerRow * tileSize,
            16,
            16
        };

        // Tile position in the world space.
        SDL_Rect tilePos = {
            (data.position.x - viewPort.x) * scale,
            (data.position.y - viewPort.y) * scale,
            data.position.w * scale,
            data.position.h * scale
        };

        // TODO: change the atlas to the objetAtlas
        SDL_RenderCopy(renderer, atlases[mapAtlas], &tileTexture, &tilePos);
    }

    // Render Enemies

    // Renders the player
    const Player *player = game->getPlayer();
    const SDL_Rect playerSprite = player->getSpritePos();
    const SDL_Rect *rawPlayerPos = player->getPosition();
    const std::string playerAtlas = player->getAtlasName();
    bool left = player->isLookingLeft();

    SDL_Rect playerPos = *rawPlayerPos;
    playerPos.x = (rawPlayerPos->x - viewPort.x) * scale;
    playerPos.y = (rawPlayerPos->y - viewPort.y) * scale;
    playerPos.w *= scale;
    playerPos.h *= scale;

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (left)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_RenderCopyEx(renderer, atlases[playerAtlas], &playerSprite, &playerPos, 
                     0.0, nullptr, flip);

    // Renders the weapon
    if (player->isAttacking())
    {
        const std::pair<int, int> *offset = player->getSwordSpriteOffset();
        int spriteSize = player->getSpriteSize();

        // Sword position relative to the player to world pos.
        SDL_Rect swordPos;
        swordPos.x = (rawPlayerPos->x + offset->first - viewPort.x) * scale;
        swordPos.y = (rawPlayerPos->y + offset->second - viewPort.y) * scale;
        swordPos.w = spriteSize * scale;
        swordPos.h = spriteSize * scale;

        SDL_Rect swordSprite = playerSprite;
        swordSprite.y += spriteSize;

        SDL_RenderCopyEx(renderer, atlases[playerAtlas], &swordSprite, 
                         &swordPos, 0.0, nullptr, flip);
    }

    // Render Debug
    if (game->isInDebugMode())
    {
        const SDL_Rect swordHitbox = player->getSwordHitbox();
        const SDL_Rect *playerCol  = player->getColision();
        
        SDL_Rect swordWorldHitbox = {
            rawPlayerPos->x + swordHitbox.x,
            rawPlayerPos->y + swordHitbox.y,
            swordHitbox.w,
            swordHitbox.h
        };
        
        SDL_Rect playerWorldHitbox = {
            rawPlayerPos->x + playerCol->x,
            rawPlayerPos->y + playerCol->y,
            playerCol->w,
            playerCol->h
        };
        
        SDL_Color blue = { 0, 0, 255, 255 };
        SDL_Color green = { 0, 255, 0, 255 };
        if (player->isAttacking())
        {
            drawHitbox(swordWorldHitbox, *game->getCamera(), blue);
        }
        drawHitbox(playerWorldHitbox, *game->getCamera(), green);
    }

    // Render UI

    // Updates the Render
    SDL_RenderPresent(renderer);
}

void RenderEngine::drawHitbox(const SDL_Rect &worldHitbox, 
                              const Camera &camera, SDL_Color color) const
{
    const SDL_Rect& cameraViewport = camera.getViewPort();

    SDL_Rect screenHitbox = {
        (worldHitbox.x - cameraViewport.x) * scale,
        (worldHitbox.y - cameraViewport.y) * scale,
        worldHitbox.w * scale,
        worldHitbox.h * scale
    };

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 100);
    SDL_RenderFillRect(renderer, &screenHitbox);

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawRect(renderer, &screenHitbox);
}

bool RenderEngine::is2FrameAnimation(uint8_t tileId) const
{
    bool single = true;

    switch (tileId)
    {
        case blueFlower:
        case whiteFlower:
        case redMushroom:
            single = false;
            break;
        default:
            single = true;
            break;
    }

    return single;
}

int RenderEngine::hasAnimation(uint8_t tileId) const
{
    bool animated = false;

    switch (tileId)
    {
        case waterFull:

        case waterInsideCornerUL:
        case waterInsideCornerDL:
        case waterInsideCornerUR:
        case waterInsideCornerDR:

        case waterOutsideCornerUL:
        case waterOutsideCornerDL:
        case waterOutsideCornerUR:
        case waterOutsideCornerDR:

        case waterSideU:
        case waterSideL:
        case waterSideR:
        case waterSideD:

        case blueFlower:
        case whiteFlower:
        case redMushroom:
            animated = true;
            break;
        default:
            animated = false;
            break;
    }

    return animated;
}
