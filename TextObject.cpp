//
//#include"SDL_utils.h"
//
//TextObject::TextObject() {}
//
//TextObject::~TextObject() {
//	SDL_DestroyTexture(texture_);
//}
//
//void TextObject::SetText(const std::string& text) {
//	str_val = text;
//}
//
//void TextObject::SetColor(const int& type) {
//	if (type == RED_TEXT) {
//		SDL_Color color = {255, 0, 0};
//		text_color = color;
//	}
//	else if (type == WHITE_TEXT) {
//		SDL_Color color = {255, 255, 255};
//		text_color = color;
//	}
//	else if (type == BLACK_TEXT) {
//		SDL_Color color = {0, 0, 0};
//		text_color = color;
//	}
//	else if (type == GREEN_TEXT) {
//		SDL_Color color = {34, 139, 34};
//		text_color = color;
//	}
//	else if (type == PINK_TEXT) {
//		SDL_Color color = {249, 109, 109};
//		text_color = color;
//	}
//	else if (type == LIGHT_YELLOW_TEXT) {
//		SDL_Color color = {238, 232, 170};
//		text_color = color;
//	}
//}
//
//
