#include "Pipeline.hpp"

#include <iostream>
#include "Debug.hpp"

void pipeline::rasterise(Graphics &graphics, model::Model &model,
	std::vector<Fragment> frags) {
	for (unsigned int i=0; i<model.triangles.size(); ++i) {
			// get the triangles and colours
			Triangle tri = model.triangles[i];

			// get the fragments
			Fragment f1 = frags[tri[0]];
			Fragment f2 = frags[tri[1]];
			Fragment f3 = frags[tri[2]];

			// draw triangle with solid colour
			SDL_Colour tri_colour = model.colours[i];
			graphics.triangle(f1, f2, f3, tri_colour);
		}
}

void pipeline::transform_vertices(model::Model &model,
	Matrix<float> &mvp) {
	for (unsigned int i=0; i<model.vertices.size(); i++) {
		bool visible = model.visible_vertices[i];
		if (visible) {
			// transform if vector is visible
			Vector v = model.vertices[i];
			Vector fv_4d = mvp.mult_vector(v);
			Vector fv_3d = fv_4d.project_to_3d();

			// replace existing vector
			model.vertices[i] = fv_3d;
		}
	}
}

model::Model pipeline::backface_cull(model::Model &model, Vector camera_pos) {
	// culled model
	model::Model visible_model;

	// mark all vertices as invisible
	std::vector<bool> vertex_visible(model.vertices.size(), false);

	// backface culling
	for (unsigned int i=0; i<model.triangles.size(); ++i) {
		Vector face_center = model.triangle_centers[i];
		Vector face_normal = model.triangle_normals[i];

		// calculate the viewing direction
		Vector view_direction = face_center - camera_pos;

		// calculate dotproduct between two to find angle
		float dot = face_normal.dot(view_direction);

		// triangle is visible
		if (dot > 0.0f) {
			// mark vertices in triangle as visible
			Triangle t = model.triangles[i];
			vertex_visible[t[0]] = true;
			vertex_visible[t[1]] = true;
			vertex_visible[t[2]] = true;

			// get the colour of the triangle
			SDL_Colour col = model.colours[i];

			// add triangle details to the visible model
			visible_model.triangles.push_back(t);
			visible_model.colours.push_back(col);
			visible_model.triangle_centers.push_back(face_center);
			visible_model.triangle_normals.push_back(face_normal);
		}
	}

	// set the vertices and visibility
	visible_model.vertices = model.vertices;
	visible_model.visible_vertices = vertex_visible;

	// set the surface attributes
	visible_model.surface_attribute = model.surface_attribute;

	// set the texture properties
	visible_model.textured = model.textured;
	visible_model.uv_coordinates = model.uv_coordinates;
	visible_model.texture = model.texture;

	// return the visible model
	return visible_model;
}

std::vector<Fragment> pipeline::to_screen_coordinates(Graphics &graphics,
	model::Model &model) {
	std::vector<Fragment> frags;

	for (unsigned int i=0; i<model.vertices.size(); i++) {
		bool visible = model.visible_vertices[i];
		if (visible) {
			Vector v = model.vertices[i];
			Fragment screen_coords = graphics.to_screen(v);
			screen_coords.z = v.z;
			frags.push_back(screen_coords);
		}
		else {
			Fragment empty = {0, 0, 0};
			frags.push_back(empty);
		}
	}

	return frags;
}
