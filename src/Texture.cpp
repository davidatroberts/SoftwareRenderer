#include "Texture.hpp"

Texture::Texture() {

}

bool Texture::load(std::string file_name) {
  // try loading the file
  SDL_Surface *raw_image = IMG_Load(file_name.c_str());
  if (!raw_image)
    return false;

  // set an optimised version
  texture_ = std::unique_ptr<SDL_Surface>(SDL_DisplayFormat(raw_image));

  

  return true;
}

SDL_Colour Texture::map(Vector2 uv) {

}
