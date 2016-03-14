#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <array>
#include <memory>
#include <tuple>
#include "SDL/SDL.h"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Vector2.hpp"

struct Triangle {
	unsigned int a;
	unsigned int b;
	unsigned int c;
	unsigned int& operator[](int i) {
		switch(i) {
			case 0:
				return a;
			case 1:
				return b;
			case 2:
				return c;
			default:
				return a;
		}
	}
};
typedef struct Triangle Triangle;

struct Fragment {
	int x;
	int y;
	float z;
};
typedef struct Fragment Fragment;

struct ScreenTriangle {
	std::array<Vector, 3> fragments;
	std::array<Vector2, 3> uv_coordinates;
	std::array<SDL_Colour, 3> colours;
	std::shared_ptr<Texture> texture;
	bool textured;
};
typedef struct ScreenTriangle ScreenTriangle;

class Vector;
class Graphics {
public:
	Graphics(uint16_t *buffer, int width, int height,
		SDL_PixelFormat *format);
	~Graphics();

	static void sort_points(Fragment &p1, Fragment &p2, Fragment &p3);
	static int sgn(int x);

	void clear();
	void clear_zbuffer();
	void draw_pixel(int x, int y, SDL_Colour &colour);
	void draw_pixel(int x, int y, float z, SDL_Colour &colour);
	void line(Fragment &p1, Fragment &p2, SDL_Colour &colour);
	void line(Vector &v1, Vector &v2, SDL_Colour &colour);
	void triangle(Fragment &p1, Fragment &p2, Fragment &p3, SDL_Colour &colour);
	void triangle(ScreenTriangle triangle);
	Fragment to_screen(Vector &v);

private:
	void flat_triangle(Fragment &p1, Fragment &p2, Fragment &p3,
		SDL_Colour &colour);
	void flat_triangle(ScreenTriangle tri);

	uint16_t *buffer_;
	float *z_buffer_;
 	int width_;
 	int height_;
	const SDL_PixelFormat *format_;
};

#endif
