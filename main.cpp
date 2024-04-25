#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>
#include "Menu.h"
#include "SDL_utils.h"

using namespace std;

#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;
//Mix_Chunk* game_over=loadSound("gameover.mp3");

Gallery* gallery = nullptr;

int main(int argc, char* argv[])
{
    srand(0);
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    Menu menu(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    Select choice = menu.ShowMenu();
    if (choice == PLAY)
    {
//        cout<<"choice Play"<<endl;
        gallery = new Gallery(renderer);
        Game game(BOARD_WIDTH, BOARD_HEIGHT);
        SDL_Event e;
        auto start = CLOCK_NOW();
        bool isquit=false;
        renderGamePlay(renderer, game, gallery);
        renderSplashScreen();
        while ( !isquit)
        {
//            cout <<"ve game chinh"<<endl;
            while (SDL_PollEvent(&e))
            {
//                cout <<"nhan su kien game"<<endl;
                interpretEvent(e, game,isquit);
            }
            if(game.isGameRunning()){
                auto end = CLOCK_NOW();
                ElapsedTime elapsed = end - start;
                if (elapsed.count() > STEP_DELAY)
                {
                    game.nextStep();
                    renderGamePlay(renderer, game, gallery);
                    start = end;
                }
            SDL_Delay(1);
            }
            else if(game.isGameOver()){
                SDL_Rect GameOverRect = {200, 200, 500, 200};
                SDL_RenderCopy(renderer, gallery->getImage(PIC_GAME_OVER), NULL, &GameOverRect);
                //Mix_PlayChannel(-1,game_over,0);
                SDL_RenderPresent(renderer);
            }
        }
}
    delete gallery;
    quitSDL(window, renderer);
    return 0;

}
