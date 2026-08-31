#include "RenderEngine.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

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

    // Renders the player
    const SDL_Rect *playerSprite = game->getPlayer()->getSpritePos();
    const SDL_Rect *rawPlayerPos = game->getPlayer()->getPosition();

    SDL_Rect playerPos = *rawPlayerPos;
    playerPos.h *= scale;
    playerPos.w *= scale;

    SDL_RenderCopy(renderer, atlases["assets/playerAtlas.png"], playerSprite, &playerPos);

    // Updates the Render
    SDL_RenderPresent(renderer);
}
