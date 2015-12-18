#ifndef LIGHTING_H
#define LIGHTING_H

#include "SDL/SDL.h"
#include "Vector.hpp"

namespace model {
	struct Model;
}

namespace lighting {
	struct Light {
		Vector view_position;
		Vector ambient;
		Vector diffuse;
		Vector specular;
		struct {
			float constant;
			float linear;
			float exponent;
		} attenuation;
	};
	typedef struct Light Light;

	struct Surface {
		Vector ambient;
		Vector diffuse;
		Vector specular;
		float shininess;
	};
	typedef struct Surface Surface;

	struct LightResult {
		Vector ambient;
		Vector diffuse;
		Vector specular;

		LightResult& operator+=(const LightResult& other) {
			ambient += other.ambient;
			diffuse += other.diffuse;
			specular += other.specular;
			return *this;
		};
	};
	typedef struct LightResult LightResult;

	float attenuate(float constant, float linear, float exponent, float d);
	lighting::LightResult calculate_point_light(lighting::Light &light, 
		lighting::Surface &surface, Vector &position, Vector &normal);
	std::vector<lighting::LightResult> calculate_point_lights(
		std::vector<lighting::Light> &lights, model::Model &model);
	std::vector<SDL_Color> lightresults_to_colours(
		std::vector<lighting::LightResult> &lightresults);
}

#endif