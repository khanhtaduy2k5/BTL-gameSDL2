
#ifndef GALLERY_H
#define GALLERY_H

#include <vector>
#include <string>


//#if defined(_WIN64) || defined(_WIN32)
//    #include <SDL.h>
//#else
    #include <SDL.h>
//#endif
enum PictureID {
    PIC_CHERRY ,PIC_PINEAPPLE , PIC_APPLE ,
    PIC_SNAKE_VERTICAL,
    PIC_SNAKE_HORIZONTAL, PIC_SNAKE_HEAD, PIC_COUNT, PIC_SNAKE_MAP
};

class Gallery
{
    SDL_Texture* pictures[PIC_COUNT];
    SDL_Renderer* renderer;
    SDL_Texture* loadTexture(std::string path);
public:
    Gallery(SDL_Renderer* renderer_);
    ~Gallery();

    void loadGamePictures();
    SDL_Texture* getImage(PictureID id) const { return pictures[id]; }
};

#endif
