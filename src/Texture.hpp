#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Vector2.hpp"

class Texture {
public:
  Texture();

  bool load(std::string file_name);
  SDL_Colour map(Vector2 uv);

private:
  SDL_Colour get_texel(int x, int y);

  std::unique_ptr<SDL_Surface> texture_;
};

#endif
