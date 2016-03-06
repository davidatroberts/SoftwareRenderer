#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "SDL/SDL.h"
#include "Graphics.hpp"
#include "Lighting.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Vector2.hpp"

namespace model {
	// all indices in clockwise order
	struct Model {
		std::vector<Vector> vertices;
		std::vector<Vector> triangle_normals;
		std::vector<Vector> triangle_centers;
		std::vector<bool> visible_vertices;
		std::vector<Triangle> triangles;
		std::vector<SDL_Colour> colours;
		std::vector<Vector2> uv_coordinates;
		lighting::Surface surface_attribute;
		Texture texture;
	};
	typedef struct Model Model;

	void calculate_normals(model::Model &model);
	void calculate_centers(model::Model &model);
	void create_octahedron(model::Model &model, int resolution);
	int create_vertex_line(Vector &from, Vector &to,
		std::vector<Vector> &vertices, int steps, int v);
	int create_lower_strip(std::vector<Triangle> &triangles,
		int steps, int v_top, int v_bottom, int tri_index);
	int create_upper_strip(std::vector<Triangle> &triangles,
		int steps, int v_top, int v_bottom, int tri_index);
	model::Model cube();
	model::Model octahedron();
	model::Model sphere(int subdivisions);
}

#endif
