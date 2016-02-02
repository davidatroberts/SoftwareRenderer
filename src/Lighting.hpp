#ifndef LIGHTING_H
#define LIGHTING_H

#include <memory>
#include "SDL/SDL.h"
#include "Vector.hpp"

namespace model {
	struct Model;
}

namespace lighting {
	// struct for storing face attributes
	struct Surface {
		Vector ambient;
		Vector diffuse;
		Vector specular;
		float shininess;
	};
	typedef struct Surface Surface;

	// struct for storing light result after calculations
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

	// util struct for attenuation
	struct Attenuation {
		float constant;
		float linear;
		float exponent;
	};
	typedef struct Attenuation Attenuation;

	// base class for Light
	class Light {
	public:
		Light(Vector view_position, Vector ambient, Vector diffuse,
			Vector specular);
		virtual lighting::LightResult calculate_light(lighting::Surface &surface, 
			Vector &position, Vector &normal) = 0;
		virtual ~Light() = 0;

		Vector view_position;
		Vector ambient;
		Vector diffuse;
		Vector specular;
	};

	class PointLight: public Light {
	public:
		PointLight(Vector view_position, Vector ambient, Vector diffuse,
			Vector specular, Attenuation attenuation);
		lighting::LightResult calculate_light(lighting::Surface &surface,
			Vector &position, Vector &normal);
		~PointLight();

		lighting::Attenuation attenuation;
	};

	class DirectionalLight: public Light {
	public:
		DirectionalLight(Vector view_position, Vector ambient, Vector diffuse,
			Vector specular);
		lighting::LightResult calculate_light(lighting::Surface &surface,
			Vector &position, Vector &normal);
		~DirectionalLight();
	};

	class SpotLight: public Light {
	public:
		SpotLight(Vector view_position, Vector ambient, Vector diffuse,
			Vector specular, Attenuation attenuation, Vector view_direction, 
			float cutoff, float exponent);
		lighting::LightResult calculate_light(lighting::Surface &surface,
			Vector &position, Vector &normal);
		~SpotLight();

		lighting::Attenuation attenuation;
		Vector view_direction;
		float cutoff;
		float exponent;
	};

	float attenuate(float constant, float linear, float exponent, float d);
	std::vector<lighting::LightResult> calculate_lights(
		std::vector<std::shared_ptr<lighting::Light>> &lights, 
		model::Model &model);
	std::vector<SDL_Color> lightresults_to_colours(
		std::vector<lighting::LightResult> &lightresults);
}

#endif