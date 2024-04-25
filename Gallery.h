
#ifndef GALLERY_H
#define GALLERY_H

#include <vector>
#include <string>
#include <SDL.h>

enum PictureID {
    PIC_CHERRY ,PIC_PINEAPPLE , PIC_APPLE ,PIC_CARROT , PIC_LEMON,
    PIC_SNAKE_VERTICAL, PIC_HOW_TO_PLAY, PIC_BACK,
    PIC_SNAKE_HORIZONTAL, PIC_SNAKE_HEAD, PIC_SNAKE_MAP,PIC_SNAKE_START,PIC_GAME_OVER,PIC_COUNT
};

class Gallery
{
    SDL_Texture* pictures[30];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(std::string path);
public:
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif
