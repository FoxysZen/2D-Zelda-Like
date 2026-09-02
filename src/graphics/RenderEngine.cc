#include "RenderEngine.h"
#include <ostream>

RenderEngine::RenderEngine() {}
RenderEngine::~RenderEngine() {}

int RenderEngine::init(const char *title, int width, int height, int _scale)
{
    scale = _scale;

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
    // TEMPORAL
    SDL_SetRenderDrawColor(renderer, 155, 188, 15, 255);
    SDL_RenderClear(renderer);

    // Renders the Map
    MapData *map = game->getTileMap()->getCurrentMap();
    const int mapWidth = map->mapWidth;
    const int tileSize = map->tileSize;
    const std::string mapAtlas = map->atlas;

    int atlasWidth;
    SDL_QueryTexture(
        atlases[mapAtlas],
        nullptr,
        nullptr,
        &atlasWidth,
        nullptr
    );
    const int tilesPerRow = atlasWidth / tileSize;

    // Base tiles
    for (size_t id = 0, size = map->worldMap.size(); id < size; ++id)
    {
        int tileId = map->worldMap[id];

        // Tile position in the PNG
        int posX = id % mapWidth * tileSize * scale;
        int posY = id / mapWidth * tileSize * scale;
        SDL_Rect tilePos = {posX, posY, tileSize * scale, tileSize * scale};

        // Tile position in the world space.
        int i = tileId % tilesPerRow * tileSize;
        int j = tileId / tilesPerRow * tileSize;
        SDL_Rect tileTexture  = {i, j, tileSize, tileSize};

        SDL_RenderCopy(renderer, atlases[mapAtlas], &tileTexture, &tilePos);
    }

    // Decoration tiles
    for (size_t id = 0, size = map->decorationMap.size(); id < size; ++id)
    {
        int tileId = map->decorationMap[id];
        if (tileId == 0) continue;

        // Tile position in the PNG
        int posX = id % mapWidth * tileSize * scale;
        int posY = id / mapWidth * tileSize * scale;
        SDL_Rect tilePos = {posX, posY, tileSize * scale, tileSize * scale};

        // Tile position in the world space.
        int i = tileId % tilesPerRow * tileSize;
        int j = tileId / tilesPerRow * tileSize;
        SDL_Rect tileTexture  = {i, j, tileSize, tileSize};

        SDL_RenderCopy(renderer, atlases[mapAtlas], &tileTexture, &tilePos);
    }

    // Render Objects
    // Render Enemies

    // Renders the player
    const SDL_Rect *playerSprite = game->getPlayer()->getSpritePos();
    const SDL_Rect *rawPlayerPos = game->getPlayer()->getPosition();
    const std::string playerAtlas = game->getPlayer()->getAtlasName();

    SDL_Rect playerPos = *rawPlayerPos;
    playerPos.h *= scale;
    playerPos.w *= scale;

    SDL_RenderCopy(renderer, atlases[playerAtlas], playerSprite, &playerPos);

    // Render UI

    // Updates the Render
    SDL_RenderPresent(renderer);
}
