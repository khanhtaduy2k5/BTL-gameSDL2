
#include"SDL_utils.h"
#include<SDL_ttf.h>
TextObject::TextObject() {}

TextObject::~TextObject() {
	SDL_DestroyTexture(texture_);
}

void TextObject::SetText(const std::string& text) {
	str_val = text;
}

void TextObject::SetColor(const int& type) {
	if (type == RED_TEXT) {
		SDL_Color color = {255, 0, 0};
		text_color = color;
	}
	else if (type == WHITE_TEXT) {
		SDL_Color color = {255, 255, 255};
		text_color = color;
	}
	else if (type == BLACK_TEXT) {
		SDL_Color color = {0, 0, 0};
		text_color = color;
	}
	else if (type == GREEN_TEXT) {
		SDL_Color color = {34, 139, 34};
		text_color = color;
	}
	else if (type == PINK_TEXT) {
		SDL_Color color = {249, 109, 109};
		text_color = color;
	}
	else if (type == LIGHT_YELLOW_TEXT) {
		SDL_Color color = {238, 232, 170};
		text_color = color;
	}
}

//void TextObject::CreateGameText(SDL_Renderer* renderer,string input, int x, int y,int size)
//{
//    if(TTF_Init()==-1){
//        cout <<"loi "<<endl;
//    }
//    TTF_Font* font = TTF_OpenFont("font/VBODONP.ttf", size);
//        if (font == nullptr) {
//            cout<< "Failed to load font: " << TTF_GetError() << endl;
//    }
//    SDL_Color White = {255,255,255};
//    SDL_Surface *textSurface = TTF_RenderText_Solid(font, input.c_str(), White);
//    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
////    SDL_FreeSurface(textSurface);
//    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
//    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
//    SDL_DestroyTexture(text);
//}
