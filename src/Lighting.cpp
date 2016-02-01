#include <algorithm>
#include <cmath>
#include <vector>

#include "Lighting.hpp"
#include "Model.hpp"

namespace lighting {

// Light Abstract Base Class
Light::Light(Vector view_position, Vector ambient, Vector diffuse,
	Vector specular) 
:view_position(view_position), ambient(ambient), diffuse(diffuse), 
specular(specular) {
}

Light::~Light() {
}

// Point Light Class
PointLight::PointLight(Vector view_position, Vector ambient, Vector diffuse,
	Vector specular, Attenuation attenuation)
:Light(view_position, ambient, diffuse, specular), attenuation(attenuation) {
}

lighting::LightResult PointLight::calculate_light(lighting::Surface &surface,
			Vector &position, Vector &normal) {
	// define lighting result
	lighting::LightResult result = {
		Vector(0.0, 0.0, 0.0),
		Vector(0.0, 0.0, 0.0),
		Vector(0.0, 0.0, 0.0)
	};

	// direction to light
	Vector light_direction = position - view_position;
	light_direction = light_direction.normalized();

	// compute attenuation factor
	float light_distance = light_direction.magnitude();
	float atten = attenuate(attenuation.constant,
		attenuation.linear, attenuation.exponent, light_distance);

	// accumulate ambient
	result.ambient += surface.ambient * ambient * atten;

	// accumulate diffuse 
	float n_dot_l = std::max(0.0f, normal.dot(light_direction));
	result.diffuse += (surface.diffuse * diffuse * atten) * n_dot_l;

	if (n_dot_l > 0.0) {
		// accumulate specular if fragment is illuminated
		Vector view_direction = position.normalized();
		Vector reflection = light_direction.reflect(normal);
		float specular = std::max(0.0f, reflection.dot(view_direction));

		result.specular += surface.specular * specular 
			* pow(specular, surface.shininess) * atten;
	}

	return result;
}

PointLight::~PointLight() {
}

float attenuate(float constant, float linear, float exponent, float d) {
	return 1.0f/(constant + (linear*d) + (exponent*(d*d)));
}


std::vector<lighting::LightResult> calculate_lights(
	std::vector<std::shared_ptr<lighting::Light>> &lights, model::Model &model) {
	std::vector<lighting::LightResult> results;

	for (unsigned int i=0; i<model.triangles.size(); i++) {
		// get the details for the face
		Vector face_position = model.triangle_centers[i];
		Vector face_normal = model.triangle_normals[i];

		// to store light calculations
		lighting::LightResult result = {
			Vector(0.0, 0.0, 0.0),
			Vector(0.0, 0.0, 0.0),
			Vector(0.0, 0.0, 0.0)
		};

		// calculate for each light
		for (auto light: lights) {
			result += light->calculate_light(model.surface_attribute, 
				face_position, face_normal);
		}

		results.push_back(result);
	}

	return results;
}

std::vector<SDL_Color> lightresults_to_colours(
	std::vector<lighting::LightResult> &lightresults) {
	std::vector<SDL_Color> colours;
	for (lighting::LightResult light: lightresults) {
		SDL_Color colour = {
			(Uint8)(((light.ambient.x + light.diffuse.x + light.specular.x)/3.0)
				*255),
			(Uint8)(((light.ambient.y + light.diffuse.y + light.specular.y)/3.0)
				*255),
			(Uint8)(((light.ambient.z + light.diffuse.z + light.specular.z)/3.0)
				*255),
		};

		colours.push_back(colour);
	}

	return colours;
}

}