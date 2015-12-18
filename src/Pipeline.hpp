#ifndef PIPELINE
#define PIPELINE

#include <vector>
#include "Graphics.hpp"
#include "Matrix.hpp"
#include "Model.hpp"
#include "Vector.hpp"

namespace pipeline {
	void rasterise(Graphics &graphics, model::Model &model,
		std::vector<Fragment> frags);
	void transform_vertices(model::Model &model, Matrix<float> &mvp);
	model::Model backface_cull(model::Model &model, Vector camera_pos);
	std::vector<Fragment> to_screen_coordinates(Graphics &graphics,
		model::Model &model);
}

#endif