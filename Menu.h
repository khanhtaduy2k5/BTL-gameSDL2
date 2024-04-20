#ifndef MENUGAME_H
#define MENUGAME_H

#include "SDL_utils.h"
#include "Gallery.h"

enum Select{
    PLAY,
    HOW_TO_PLAY,
    EXIT,
    QUIT
};
class Menu
{
public:

    Menu(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    ~Menu();

    Select ShowMenu();
    void RenderHowToPlay();
private:
    SDL_Event e;
    const int SizeSelectionW = SCREEN_WIDTH/3;
    const int SizeSelectionH = 100;

    SDL_Window* window;
    SDL_Renderer* renderer;

    Gallery* gallery;

};

#endif // MENUGAME_H
