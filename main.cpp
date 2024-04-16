#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

#include "SDL_utils.h"
using namespace std;


#define CLOCK_NOW chrono::system_clock::now
typedef chrono::duration<double> ElapsedTime;

Gallery* gallery = nullptr;

int main(int argc, char* argv[])
{
    srand(0);
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    gallery = new Gallery(renderer);
    Game game(BOARD_WIDTH, BOARD_HEIGHT);
    SDL_Event e;

    renderSplashScreen();
    auto start = CLOCK_NOW();
    renderGamePlay(renderer, game, gallery);
    bool isquit=false;

    while (game.isGameRunning() && !isquit) {
        while (SDL_PollEvent(&e)) {
            interpretEvent(e, game,isquit);
        }

        auto end = CLOCK_NOW();
        ElapsedTime elapsed = end-start;
        if (elapsed.count() > STEP_DELAY) {
            game.nextStep();
            renderGamePlay(renderer, game, gallery);
            start = end;
        }
        SDL_Delay(1);
    }
    renderGameOver(renderer, game);
    updateRankingTable(game);

    delete gallery;
    quitSDL(window, renderer);
    return 0;

}
