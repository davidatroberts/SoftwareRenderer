#ifndef SDL_UTIL
#define SDL_UTIL

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

namespace sdl_util {
  SDL_Colour lerp_colour(SDL_Colour c1, SDL_Colour c2, float alpha);
	SDL_Colour scale_colour(SDL_Colour c, float alpha);
	SDL_Colour add_colour(SDL_Colour c1, SDL_Colour c2);
}

#endif
