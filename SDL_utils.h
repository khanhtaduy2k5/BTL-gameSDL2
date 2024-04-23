
#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Game.h"
#include "constants.h"
#include "Gallery.h"
#include "Snake.h"
#include "Position.h"

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal = false);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle) ;

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();
void renderSplashScreen();
void renderGamePlay(SDL_Renderer*, const Game& game, Gallery* gallery);
void renderGameOver(SDL_Renderer* renderer, const Game& game);
void interpretEvent(SDL_Event e, Game& game, bool& isquit);
void updateRankingTable(const Game& game);
std::string createText(int score);
void drawText(SDL_Renderer* renderer, int score);
void CreateGameText(SDL_Renderer* renderer,std::string input, int x, int y);
#endif
