#include "Menu.h"
#include "SDL_utils.h"

Menu::Menu(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : window(window), renderer(renderer)
    {
        gallery = new Gallery(renderer);
    }

Menu::~Menu()
{

}

Select Menu::ShowMenu()
{
    bool isMenu = true;
    SDL_Event e;
    Select choice = PLAY;
    while (isMenu)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect backgroundRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect exitRect = {80,490,170,100};
        SDL_Rect playRect = {650,490,170,100};
        SDL_Rect howToPlayRect={765,90,60,80};
        if(gallery->getImage(PIC_SNAKE_START)==nullptr){
            std::cout<<"Unable to load texture"<<std::endl;
        }

        SDL_RenderCopy(renderer,gallery->getImage(PIC_SNAKE_START), NULL, &backgroundRect);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT) {
                choice = QUIT;
                isMenu = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point p ={x, y};
                if (SDL_PointInRect(&p, &playRect))
                {
                    choice = PLAY;
                    isMenu = false;
                }
                else if (SDL_PointInRect(&p, &howToPlayRect))
                {
                    choice = HOW_TO_PLAY;
                    RenderHowToPlay();
                }
                else if (SDL_PointInRect(&p, &exitRect))
                {
                    choice = EXIT;
                    isMenu = false;
                }
            }
        }
    }

    return choice;
}

void Menu::RenderHowToPlay()
{
    bool isRunning = true;
    SDL_Event e;

    while (isRunning)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Rect howtoPlayRect={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        SDL_RenderCopy(renderer,gallery->getImage(PIC_HOW_TO_PLAY), NULL, &howtoPlayRect);
        SDL_Rect backRect = {0, 0, 100, 100};
        SDL_RenderCopy(renderer,gallery->getImage(PIC_BACK) , NULL, &backRect);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                isRunning = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point p ={x, y};
                if (SDL_PointInRect(&p, &backRect))
                {
                    isRunning = false;
                }
            }
        }
    }
}
