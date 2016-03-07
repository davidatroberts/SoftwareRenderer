#include "Texture.hpp"

#include <cmath>
#include "SDLUtil.hpp"

Texture::Texture()
:loaded_(false) {

}

bool Texture::load(std::string file_name) {
  // try loading the file
  SDL_Surface *raw_image = IMG_Load(file_name.c_str());
  if (!raw_image)
    return false;

  // set an optimised version
  texture_ = std::shared_ptr<SDL_Surface>(SDL_DisplayFormat(raw_image));
	loaded_ = true;
  return true;
}

SDL_Colour Texture::map(Vector2 uv) {
	// return white if not loaded
	if (!loaded_)
		return {255, 255, 255};

  // map to texture coordinates
  float x = (uv.x * texture_->w);
  float y = (uv.y * texture_->h);

  // split into int, fractional parts
  float x_int, y_int;
  float x_frac = std::modf(x, &x_int);
  float y_frac = std::modf(y, &y_int);

  // wrap the textures around
  int x_wrap = ((int)x_int)%texture_->w;
  int y_wrap = ((int)y_int)%texture_->h;

  // get four surrounding points
  SDL_Colour bottom_left = get_texel(x_wrap, y_wrap);
  SDL_Colour bottom_right = get_texel(x_wrap+1, y_wrap);
  SDL_Colour top_left = get_texel(x_wrap, y_wrap+1);
  SDL_Colour top_right = get_texel(x_wrap+1, y_wrap+1);

  // interpolate between the points
  SDL_Colour bottom_middle = sdl_util::lerp(bottom_left, bottom_right, x_frac);
  SDL_Colour top_middle = sdl_util::lerp(top_left, top_right, x_frac);
  SDL_Colour point = sdl_util::lerp(bottom_middle, top_middle, y_frac);

  return point;
}

SDL_Colour Texture::get_texel(int x, int y) {
  uint16_t pixel = *((uint16_t*)texture_->pixels+y*texture_->w+x);

  SDL_Colour colour;
  SDL_GetRGB(pixel, texture_->format, &colour.r, &colour.g, &colour.b);

  return colour;
}
