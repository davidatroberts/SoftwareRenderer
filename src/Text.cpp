#include "Text.hpp"

Text::Text(SDL_Surface *surface): surface_(surface) {

}

void Text::render_string(int x, int y, TTF_Font *font, SDL_Color colour, 
	std::string str) {
	SDL_Surface *msg = TTF_RenderText_Solid(font, str.c_str(), colour);

	SDL_Rect offset;
	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(msg, NULL, surface_, &offset);
}