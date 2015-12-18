#include "Model.hpp"

#include <iostream>

void model::calculate_normals(model::Model &model) {
	// calculate the normal for each face (triangle)
	for (unsigned int i=0; i<model.triangles.size(); ++i) {
		// get the triangle
		Triangle tri = model.triangles[i];

		// get the vertices for the triangle
		Vector v1 = model.vertices[tri[0]];
		Vector v2 = model.vertices[tri[1]];
		Vector v3 = model.vertices[tri[2]];

		// calculate the normal
		Vector normal = Vector::plane_normal(v1, v2, v3);

		// add to list
		model.triangle_normals.push_back(normal);
	}
}

void model::calculate_centers(model::Model &model) {
	// calculate the center of gravity of each face (triangle)
	for (unsigned int i=0; i<model.triangles.size(); ++i) {
		// get the triangle
		Triangle tri = model.triangles[i];

		// get the vertices for the triangle
		Vector v1 = model.vertices[tri[0]];
		Vector v2 = model.vertices[tri[1]];
		Vector v3 = model.vertices[tri[2]];

		// calculate the center of gravity
		Vector center = (v1*(1.0f/3.0f)) + (v2*(1.0f/3.0f)) + (v3*(1.0f/3.0f));

		// add to list
		model.triangle_centers.push_back(center);
	}
}

void model::create_octahedron(model::Model &model, int resolution) {
	int v = 0;
	int v_bottom = 0;
	int t = 0;

	// different quadrants for the sphere
	std::vector<Vector> directions = {
		Vector::left(),
		Vector::backward(),
		Vector::right(),
		Vector::forward()
	};

	for (int i=0; i<4; i++) {
		model.vertices[v++] = Vector::down();
	}

	// calculate bottom hemisphere
	for (int i=1; i<=resolution; i++) {
		float progress = (float)i/resolution;
		
		Vector from, to;
		model.vertices[v++] = to = Vector::lerp(Vector::down(), 
			Vector::forward(), progress);

		// calculate each quadrant
		for (int d=0; d<4; d++) {
			from = to;
			to = Vector::lerp(Vector::down(), directions[d], progress);
			t = create_lower_strip(model.triangles, i, v, v_bottom, t);
			v = create_vertex_line(from, to, model.vertices, i, v);

			v_bottom += i > 1 ? (i - 1) : 1;
		}
		v_bottom = v-1-i*4;
	}

	// calculate top hemisphere
	for (int i=resolution-1; i>=1; i--) {
		float progress = (float)i/resolution;

		Vector from, to;
		model.vertices[v++] = to = Vector::lerp(Vector::up(), Vector::forward(), 
			progress);

		// calculate each quadrant
		for (int d=0; d<4; d++) {
			from = to;
			to = Vector::lerp(Vector::up(), directions[d], progress);
			t = create_upper_strip(model.triangles, i, v, v_bottom, t);
			v = create_vertex_line(from, to, model.vertices, i, v);

			v_bottom += i+1;
		}
		v_bottom = v-1-i*4;
	}

	// make top row
	for (int i=0; i<4; i++) {
		model.triangles[t][0] = v_bottom;
		model.triangles[t][1] = v;
		model.triangles[t][2] = ++v_bottom;
		model.vertices[v++] = Vector::up();

		t++;
	}
}

int model::create_vertex_line(Vector &from, Vector &to, 
	std::vector<Vector> &vertices, int steps, int v) {
	for (int i=1; i<=steps; i++) {
		vertices[v++] = Vector::lerp(from, to, (float)i/steps);
	}

	return v;
}

int model::create_lower_strip(std::vector<Triangle> &triangles, int steps, 
	int v_top, int v_bottom, int t) {
	// make the intermediate triangles
	for (int i=1; i<steps; i++) {
		// point down
		triangles[t][0] = v_bottom;
		triangles[t][1] = v_top - 1;
		triangles[t][2] = v_top;
		t++;

		// point up
		triangles[t][0] = v_bottom++;
		triangles[t][1] = v_top++;
		triangles[t][2] = v_bottom;
		t++;
	}

	// set vertices of the  last triangle
	triangles[t][0] = v_bottom;
	triangles[t][1] = v_top - 1;
	triangles[t][2] = v_top;

	t++;
	return t;
}

int model::create_upper_strip(std::vector<Triangle> &triangles, int steps,
	int v_top, int v_bottom, int t) {
	triangles[t][0] = v_bottom;
	triangles[t][1] = v_top-1;
	triangles[t][2] = ++v_bottom;
	t++;

	// make the intermediate triangles
	for (int i=1; i<=steps; i++) {
		triangles[t][0] = v_top-1;
		triangles[t][1] = v_top;
		triangles[t][2] = v_bottom;
		t++;

		triangles[t][0] = v_bottom;
		triangles[t][1] = v_top++;
		triangles[t][2] = ++v_bottom;
		t++;
	}

	return t;
}

model::Model model::cube() {
	model::Model m;
	m.vertices = {
		Vector(-1.0f, -1.0f, -1.0f),	Vector(-1.0f, -1.0f, 1.0f),
		Vector(-1.0f, 1.0f, 1.0f), 		Vector(-1.0f, 1.0f, -1.0f),
		Vector(1.0f, -1.0f, -1.0f), 	Vector(1.0f, -1.0f, 1.0f),
		Vector(1.0f, 1.0f, 1.0f), 		Vector(1.0f, 1.0f, -1.0f)
	};
	m.triangles = {
		{1, 0, 2}, {2, 0, 3}, 
		{2, 3, 7}, {6, 2, 7}, 
		{1, 2, 5}, {5, 2, 6},
		{0, 1, 4}, {1, 5, 4}, 
		{5, 6, 4}, {6, 7, 4}, 
		{4, 3, 0}, {4, 7, 3}
	};
	calculate_normals(m);
	calculate_centers(m);

	m.visible_vertices = std::vector<bool>(m.vertices.size(), true);
	m.colours = std::vector<SDL_Color>(m.triangles.size());

	return m;
}

model::Model model::octahedron() {
	model::Model m;
	m.vertices = {
		Vector::down(), 	
		Vector::forward(),	
		Vector::left(),		
		Vector::backward(),	
		Vector::right(), 	
		Vector::up()		
	};
	m.triangles = {
		{0, 1, 2}, {0, 2, 3},
		{0, 3, 4}, {0, 4, 1}, 
		{5, 2, 1}, {5, 3, 2},
		{5, 4, 3}, {5, 1, 4}
	};
	calculate_normals(m);
	calculate_centers(m);

	m.visible_vertices = std::vector<bool>(m.vertices.size(), true);
	m.colours = std::vector<SDL_Color>(m.triangles.size());

	return m;
}

model::Model model::sphere(int subdivisions) {
	// limit subdivision
	subdivisions = (subdivisions>6) ? 6 : subdivisions;

	// calculate resolution
	int res = 1 << subdivisions;
	int vertex_res = (res+1)*(res+1)*4-(res*2-1)*3;
	int triangle_res = (1<<(subdivisions*2+3));

	// start with an octahedron
	model::Model m;
	m.vertices = std::vector<Vector>(vertex_res);
	m.triangles = std::vector<Triangle>(triangle_res);

	// create subdivided octahedron
	create_octahedron(m, res);

	// normalize the vertices
	Vector::normalize(m.vertices);

	// calculate surface attributes
	calculate_normals(m);
	calculate_centers(m);

	m.visible_vertices = std::vector<bool>(m.vertices.size(), true);
	m.colours = std::vector<SDL_Color>(m.triangles.size());

	return m;
}