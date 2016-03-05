#ifndef SDL_UTIL
#define SDL_UTIL

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

namespace sdl_util {
  SDL_Colour lerp(SDL_Colour c1, SDL_Colour c2, float alpha);
}

#endif
