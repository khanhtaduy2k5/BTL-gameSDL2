#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED
#include "SDL_utils.h"
#include <string>
#include<iostream>
using namespace std;
class TextObject {
	std::string str_val;
	SDL_Color text_color;
	SDL_Surface* surface_;
	SDL_Texture* texture_;
public:
	TextObject();
	~TextObject();
	void Init(TTF_Font* font);
	void SetText(const std::string& text);
	void SetColor(const int& type);



	enum TextColor {
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
		GREEN_TEXT = 3,
		PINK_TEXT = 4,
		LIGHT_YELLOW_TEXT = 5,
	};
};


#endif // TEXTOBJECT_H_INCLUDED
