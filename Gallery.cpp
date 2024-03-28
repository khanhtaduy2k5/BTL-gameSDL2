
#include "Gallery.h"
#include "SDL_utils.h"

#if defined(_WIN64) || defined(_WIN32)
    #include <SDL_image.h>
#else
    #include <SDL2/SDL_image.h>
#endif



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
    pictures[PIC_CHERRY] = loadTexture("mouse.png");
    pictures[PIC_SNAKE_VERTICAL] = loadTexture("snakeVertical.png");
    pictures[PIC_SNAKE_HORIZONTAL] = loadTexture("snakeHorizontal.png");
    pictures[PIC_SNAKE_HEAD] = loadTexture("snakehead1.png");
    pictures[PIC_SNAKE_MAP] = loadTexture("map.jpg");
}

