
#include <iostream>
#include "SDL_utils.h"
#include<string>
#include<sstream>

const std::string S_SCORE_TEXT = "Score: ";
TTF_Font* m_sansFont=TTF_OpenFont("font/VBODONP.ttf", 30);


void logSDLError(std::ostream& os, const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
	int screenWidth, int screenHeight, const char* windowTitle){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048) == -1){
        std::cout << "MIX AUDIO ERROR"<<Mix_GetError()<<std::endl;
    }

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed(){
    while (true) {
        SDL_Event e;

        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(0);
    }
}
float generateRandomNumber(){
    return (float) rand() / RAND_MAX;
}

void renderSplashScreen(){
    cout << "Press any key to start game" << endl;
    waitUntilKeyPressed();
}

void drawCell(SDL_Renderer* renderer, int left, int top, Position pos, SDL_Texture* texture){
	SDL_Rect cell;
	cell.x = left + pos.x * CELL_SIZE + 5;
	cell.y = top + pos.y * CELL_SIZE + 5;
	cell.w = CELL_SIZE-10;
	cell.h = CELL_SIZE-10;
	SDL_RenderCopy(renderer, texture, NULL, &cell);
}

void drawCherry(SDL_Renderer* renderer, int left, int top, Position pos, Gallery* gallery){
    if(ranD == 0)
        drawCell(renderer, left, top, pos, gallery->getImage(PIC_APPLE));
    else if(ranD == 1)
        drawCell(renderer, left, top, pos, gallery->getImage(PIC_CHERRY));
    else if(ranD == 2)
        drawCell(renderer, left, top, pos, gallery->getImage(PIC_PINEAPPLE));
    else if(ranD == 3)
        drawCell(renderer, left, top, pos, gallery->getImage(PIC_LEMON));
    else if(ranD == 4)
        drawCell(renderer, left, top, pos, gallery->getImage(PIC_CARROT));

}

void drawSnake(SDL_Renderer* renderer, int left, int top, vector<Position> pos, Gallery* gallery){
	drawCell(renderer, left, top, pos[pos.size()-1], gallery->getImage(PIC_SNAKE_HEAD));
    for (int i = pos.size() - 2; i >= 0; i--) {
        SDL_Texture* texture = gallery->getImage(
			pos[i].y == pos[i+1].y ? PIC_SNAKE_HORIZONTAL : PIC_SNAKE_VERTICAL);
        drawCell(renderer, left, top, pos[i], texture);
    }
}

void drawVerticalLine(SDL_Renderer* renderer, int left, int top, int cells){
    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left, top + cells * CELL_SIZE);
}

void drawHorizontalLine(SDL_Renderer* renderer, int left, int top, int cells){
    SDL_SetRenderDrawColor(renderer, LINE_COLOR.r, LINE_COLOR.g, LINE_COLOR.b, 0);
    SDL_RenderDrawLine(renderer, left, top, left + cells * CELL_SIZE, top);
}

void renderGamePlay(SDL_Renderer* renderer, const Game& game, Gallery* gallery){
    int top = 0, left = 0;
    SDL_SetRenderDrawColor(renderer, BOARD_COLOR.r, BOARD_COLOR.g, BOARD_COLOR.b, 0);
    SDL_RenderClear(renderer);

    SDL_Rect mrect;
    mrect.x = 0;
    mrect.x = 0;
    mrect.w = 900;
    mrect.h = 600;
    SDL_RenderCopy(renderer, gallery->getImage(PIC_SNAKE_MAP), NULL, &mrect);


    for (int x = 0; x <= BOARD_WIDTH; x++)
        drawVerticalLine(renderer, left + x*CELL_SIZE, top, BOARD_HEIGHT);
    for (int y = 0; y <= BOARD_HEIGHT; y++)
        drawHorizontalLine(renderer, left, top+y * CELL_SIZE, BOARD_WIDTH);

    drawCherry(renderer, left, top, game.getCherryPosition(), gallery);
    drawSnake(renderer, left, top, game.getSnakePositions(), gallery);
    CreateGameText(renderer, S_SCORE_TEXT,30, 600);
    CreateGameText(renderer, std::to_string(game.score), 150, 600);
    CreateGameText(renderer, "Live: ", 300,600);
    CreateGameText(renderer, std::to_string(game.live),420,600);
    SDL_RenderPresent(renderer);
}

void renderGameOver(SDL_Renderer* renderer, const Game& game){

}

void interpretEvent(SDL_Event e, Game& game, bool& isquit){
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        	case SDLK_UP: game.processUserInput(UP); break;
        	case SDLK_DOWN: game.processUserInput(DOWN); break;
        	case SDLK_LEFT: game.processUserInput(LEFT); break;
        	case SDLK_RIGHT: game.processUserInput(RIGHT); break;
        }
    }
     else if (e.type == SDL_QUIT){
        isquit=true;
     }
}

void updateRankingTable(const Game& game){

}



void CreateGameText(SDL_Renderer* renderer,std::string input, int x, int y)
{
    if(TTF_Init()==-1){
        std::cout <<"Error "<<endl;
    }
    TTF_Font* font = TTF_OpenFont("font/VBODONP.ttf", 30);
        if (font == nullptr) {
            std::cout<< "Failed to load font: " << TTF_GetError() << std::endl;
    }
    SDL_Color White = {255,255,255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, input.c_str(), White);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
}
Mix_Chunk* loadSound(std::string soundname){
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1){
        std::cout << "LỖI ÂM THANH MIX: " << Mix_GetError() << std::endl;
    }

    std::string path = "audio/" + soundname; // Construct complete path
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str()); // Load sound using complete path

    if (chunk == NULL){
        std::cout<<"ERROR loading file: " << path << ", chunk is null: " << Mix_GetError() << std::endl;
    }
    return chunk;
}



