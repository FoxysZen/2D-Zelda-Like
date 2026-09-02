#include "RenderEngine.h"
#include <iostream>
#include <ostream>

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
            int tileId = map->worldMap[y * mapWidth + x];

            // Tile position in the PNG
            int i = tileId % tilesPerRow * tileSize;
            int j = tileId / tilesPerRow * tileSize;
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
                i = tileId % tilesPerRow * tileSize;
                j = tileId / tilesPerRow * tileSize;
                tileTexture  = {i, j, tileSize, tileSize};
                
                // Tile position in the world space can be reutilized.
                
                SDL_RenderCopy(renderer, atlases[mapAtlas], &tileTexture, &tilePos);
            }
        }
    }

    // Render Objects
    // Render Enemies

    // Renders the player
    const SDL_Rect *playerSprite = game->getPlayer()->getSpritePos();
    const SDL_Rect *rawPlayerPos = game->getPlayer()->getPosition();
    const std::string playerAtlas = game->getPlayer()->getAtlasName();

    SDL_Rect playerPos = *rawPlayerPos;
    playerPos.x = (rawPlayerPos->x - viewPort.x) * scale;
    playerPos.y = (rawPlayerPos->y - viewPort.y) * scale;
    playerPos.h *= scale;
    playerPos.w *= scale;

    SDL_RenderCopy(renderer, atlases[playerAtlas], playerSprite, &playerPos);

    // Render UI

    // Updates the Render
    SDL_RenderPresent(renderer);
}
