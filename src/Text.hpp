#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Text {
public:
	Text(SDL_Surface *surface);

	void render_string(int x, int y, TTF_Font *font, SDL_Color colour, 
		std::string str);

private:
	SDL_Surface *surface_;
};

#endif