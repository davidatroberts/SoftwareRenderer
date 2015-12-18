#include "Graphics.hpp"

#include <iostream>
#include <cmath>
#include <cstdint>
#include <utility>
#include "Vector.hpp"

#define MAX_Z_DEPTH 65535

Graphics::Graphics(uint16_t *buffer, int width, int height,
	SDL_PixelFormat *format)
:buffer_(buffer), width_(width), height_(height), format_(format),
z_buffer_(new float[width*height]) {

}

Graphics::~Graphics() {
	delete[] z_buffer_;
}

void Graphics::clear() {
	memset(buffer_, 0, sizeof(uint16_t)*width_*height_);
}

void Graphics::clear_zbuffer() {
	memset(z_buffer_, MAX_Z_DEPTH, sizeof(float)*width_*height_);
}

void Graphics::draw_pixel(int x, int y, SDL_Colour &colour) {
	// check if it's within limits
	if ((x >= width_) || (y >= height_) || (x < 0) || (y < 0))
		return;

	// get uint16_t colour
	uint16_t mapped_colour = SDL_MapRGB(format_, 
		colour.r, colour.g, colour.b);

	// update buffer
	buffer_[y * width_ + x] = mapped_colour;
}

void Graphics::draw_pixel(int x, int y, float z, SDL_Colour &colour) {
	// check if it's within limits
	if ((x >= width_) || (y >= height_) || (x < 0) || (y < 0))
		return;

	// end if z is greater than z_buffer
	if (z >= z_buffer_[y * width_ + x]) 
		return;

	// update z_buffer
	z_buffer_[y * width_ + x] = z;

	// get uint16_t colour
	uint16_t mapped_colour = SDL_MapRGB(format_, 
		colour.r, colour.g, colour.b);

	// update buffer
	buffer_[y * width_ + x] = mapped_colour;
}

// Bresenham's line algorithm
void Graphics::line(int x1, int y1, int x2, int y2, SDL_Colour &colour) {
	bool changed = false;
	int x = x1;
	int y = y1;

	// estimate length
	int dx = abs(x2-x1);
	int dy = abs(y2-y1);

	// direction
	int signx = sgn(x2-x1);
	int signy = sgn(y2-y1);

	if (dy > dx) {
		int tmp = dx;
        dx = dy;
        dy = tmp;
        changed = true;
	}

	int e = 2 * dy - dx;

	for (int i=1; i<=dx; i++) {
		draw_pixel(x, y, colour);
		while(e>=0) {
			if (changed)
				x += signx;
			else
				y += signy;

			e = e-2*dx;
		}
		if (changed)
			y += signy;
		else
			x += signx;
		e = e+2*dy;
	}
	draw_pixel(x2, y2, colour);
}

// Bresenham's line algorithm with z interpolation
void Graphics::line(Fragment &f1, Fragment &f2, SDL_Colour &colour) {
	bool changed = false;
	int x = f1.x;
	int y = f1.y;

	// estimate length
	int dx = abs(f2.x-f1.x);
	int dy = abs(f2.y-f1.y);

	// direction
	int signx = sgn(f2.x-f1.x);
	int signy = sgn(f2.y-f1.y);

	if (dy > dx) {
		int tmp = dx;
        dx = dy;
        dy = tmp;
        changed = true;
	}

	int e = 2 * dy - dx;

	for (int i=1; i<=dx; i++) {
		// calculate z position
		float zb = f1.z + (f2.z - f1.z) * (((float)x-(float)f1.x)/
			((float)f2.x-(float)f1.x));

		// plot pixel
		draw_pixel(x, y, zb, colour);

		// move along line
		while(e>=0) {
			if (changed)
				x += signx;
			else
				y += signy;

			e = e-2*dx;
		}
		if (changed)
			y += signy;
		else
			x += signx;
		e = e+2*dy;
	}

	// plot final pixel
	draw_pixel(f2.x, f2.y, f2.z, colour);
}

// Bresenham's triangle algorithm
void Graphics::triangle(Fragment &p1, Fragment &p2, Fragment &p3, 
	SDL_Colour &colour) {
	// sort so that p1 is at the top
	sort_points(p1, p2, p3);

	if (p2.y == p3.y) {
		// bottom flat triangle
		flat_triangle(p1, p2, p3, colour);
	}
	else if (p1.y == p2.y) {
		// top flat triangle
		flat_triangle(p3, p1, p2, colour);
	}
	else {
		// general case, split into two triangles
		// top-flat and bottom-flat
		
		// calculate the z position for p4
		float z = p1.z + (p3.z - p1.z) * (((float)p2.y-(float)p1.y)/
			((float)p3.y-(float)p1.y));

		// create p4
		Fragment p4 = {
			 (int)(p1.x + ((float)(p2.y - p1.y) / (float)(p3.y - p1.y)) 
			 	* (p3.x - p1.x)),
			 p2.y, 
			 z
		};

		// draw the triangles
		flat_triangle(p1, p2, p4, colour);
		flat_triangle(p3, p2, p4, colour);
	}
}

void Graphics::sort_points(Fragment &p1, Fragment &p2, Fragment &p3) {
	if (p1.y < p2.y) {
		if (p1.y < p3.y) {
			if (p2.y < p3.y) {
				// p1, p2, p3
				return;
			}
			else {
				// p1, p3, p2
				std::swap(p3, p2);
				return;
			}
		}
		else {
			// p3, p1, p2
			std::swap(p2, p3);
			std::swap(p1, p2);
			return;
		}
	}
	else {
		if (p2.y < p3.y) {
			if (p1.y < p3.y) {
				// p2, p1, p3
				std::swap(p1, p2);
				return;
			}
			else {
				// p2, p3, p1
				std::swap(p1, p2);
				std::swap(p2, p3);
				return;
			}
		}
		else {
			// p3, p2, p1
			std::swap(p3, p1);
			return;
		}
	}
}

int Graphics::sgn(int x) {
	if (x < 0) {
    	return -1;
    }
    else if (x == 0) {
    	return 0;
    }
    return 1;
}

Fragment Graphics::to_screen(Vector &v) {
	int screen_x = v.x * width_ + width_ / 2.0f;
	int screen_y = -v.y * height_ + height_ / 2.0f;

	Fragment f = {
		screen_x,
		screen_y,
		0
	};

	return f; 
}

// Bresenham's triangle algorithm
void Graphics::flat_triangle(Fragment &p1, Fragment &p2, Fragment &p3, 
	SDL_Colour &colour) {
	Fragment ptemp1 = {p1.x, p1.y, p1.z};
	Fragment ptemp2 = {p1.x, p1.y, p1.z};

	bool changed1 = false;
	bool changed2 = false;

	int dx1 = abs(p2.x - p1.x);
	int dy1 = abs(p2.y - p1.y);

	int dx2 = abs(p3.x - p1.x);
	int dy2 = abs(p3.y - p1.y);

	int sgnx1 = sgn(p2.x - p1.x);
	int sgnx2 = sgn(p3.x - p1.x);

	int sgny1 = sgn(p2.y - p1.y);
	int sgny2 = sgn(p3.y - p1.y);

	if (dy1 > dx1) {
		std::swap(dx1, dy1);
		changed1 = true;
	}
	if (dy2 > dx2) {
		std::swap(dx2, dy2);
		changed2 = true;
	}

	int e1 = 2*dy1-dx1;
	int e2 = 2*dy2-dx2;

	for (int i=0; i<=dx1; i++) {
		// calculate za and zb
		float za = p1.z + (p2.z-p1.z)*(((float)ptemp1.y-(float)p1.y)/
			((float)p2.y-(float)p1.y));
		float zb = p1.z + (p3.z-p1.z)*(((float)ptemp1.y-(float)p1.y)/
			((float)p3.y-(float)p1.y));

		// set values
		ptemp1.z = za;
		ptemp2.z = zb;

		// render line
		line(ptemp1, ptemp2, colour);

		// move down line 1
		while (e1 >= 0) {
			if (changed1)
				ptemp1.x += sgnx1;
			else
				ptemp1.y += sgny1;
			e1 = e1-2*dx1;
		}

		if (changed1)
			ptemp1.y += sgny1;
		else
			ptemp1.x += sgnx1;

		e1 = e1+2*dy1;

		// move down line 2 to match y position of line 1
		while (ptemp2.y != ptemp1.y) {
			while (e2 >= 0) {
				if (changed2)
					ptemp2.x += sgnx2;
				else
					ptemp2.y += sgny2;
				e2 = e2-2*dx2;
			}

			if (changed2)
				ptemp2.y += sgny2;
			else
				ptemp2.x += sgnx2;
			e2 = e2+2*dy2;
		}
	}
}