#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace mu {
	float clamp(float x, float min_val, float max_val) {
		return std::min(std::max(x, min_val), max_val);
	}

	float smoothstep(float edge0, float edge1, float x) {
		// scale and saturate
		x = clamp((x-edge0)/(edge1-edge0), 0.0, 1.0);

		// evaluate polynomial
		return x*x*(3 - 2*x);
	}
}

#endif