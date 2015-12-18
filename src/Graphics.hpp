#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <tuple>
#include "SDL/SDL.h"

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
	void line(int x1, int y1, int x2, int y2, SDL_Colour &colour);
	void line(Fragment &p1, Fragment &p2, SDL_Colour &colour);
	void triangle(Fragment &p1, Fragment &p2, Fragment &p3, SDL_Colour &colour);
	Fragment to_screen(Vector &v);

private:
	void flat_triangle(Fragment &p1, Fragment &p2, Fragment &p3, 
		SDL_Colour &colour);

	uint16_t *buffer_;
	float *z_buffer_;
 	int width_;
 	int height_;
	const SDL_PixelFormat *format_;
};

#endif