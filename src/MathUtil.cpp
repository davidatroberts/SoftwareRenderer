#include "MathUtil.hpp"

namespace math_util {
	float lerp(float a, float b, float alpha) {
		return a*(1-alpha)+b*alpha;
	}

	float inv_lerp(float a, float b, float x) {
		return (x-a)/(b-a);
	}
}
