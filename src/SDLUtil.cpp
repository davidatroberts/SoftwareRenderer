#include "SDLUtil.hpp"

namespace sdl_util {
  SDL_Colour lerp(SDL_Colour c1, SDL_Colour c2, float alpha) {
  	uint8_t red = (uint8_t)(((float)c1.r)*(1.0f-alpha) + ((float)c2.r)*alpha);
		uint8_t green = (uint8_t)(((float)c1.g)*(1.0f-alpha) + ((float)c2.g)*alpha);
		uint8_t blue = (uint8_t)(((float)c1.b)*(1.0f-alpha) + ((float)c2.b)*alpha);

		SDL_Colour col = {
			red,
			green,
			blue
		};

		return col;
  }
}
