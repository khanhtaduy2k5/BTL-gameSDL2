
#include "SDL_utils.h"

Gallery::Gallery(SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    loadGamePictures();
}

Gallery::~Gallery()
{
    for (SDL_Texture* texture : pictures)
        SDL_DestroyTexture(texture);
}

SDL_Texture* Gallery::loadTexture(std::string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        logSDLError(std::cout, "Unable to load image " + path + " SDL_image Error: " + IMG_GetError());
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            logSDLError(std::cout, "Unable to create texture from " + path + " SDL Error: " + SDL_GetError());
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

void Gallery::loadGamePictures()
{
    pictures[PIC_SNAKE_MAP] = loadTexture("picture/map.jpg");
    pictures[PIC_SNAKE_START] = loadTexture("picture/start.jpg");
    pictures[PIC_CHERRY] = loadTexture("picture/cherry.jpg");
    pictures[PIC_PINEAPPLE] = loadTexture("picture/pineapple.jpg");
    pictures[PIC_APPLE] = loadTexture("picture/apple.jpg");
    pictures[PIC_SNAKE_VERTICAL] = loadTexture("picture/snakeVertical.png");
    pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("picture/snakeHorizontal.png");
    pictures[PIC_SNAKE_HEAD] = loadTexture("picture/snakehead1.png");
    pictures[PIC_LEMON] = loadTexture("picture/lemon.jpg");
    pictures[PIC_CARROT] = loadTexture("picture/carrot.png");
    pictures[PIC_GAME_OVER] = loadTexture("picture/gamevoer.png");


}

