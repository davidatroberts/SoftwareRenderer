#ifndef TEST_SDL_UTIL
#define TEST_SDL_UTIL

#include "bandit/bandit.h"
#include "SDLUtil.hpp"
using namespace bandit;

go_bandit([]() {
	describe("SDL Util Tests", [&]() {
		it("interpolates colours", [&]() {
			SDL_Colour c1 = {255, 0, 0};
			SDL_Colour c2 = {0, 255, 0};
			SDL_Colour result = sdl_util::lerp(c1, c2, 0.5);

			SDL_Colour expected = {127, 127, 0};
			AssertThat(result.r, Equals(expected.r));
			AssertThat(result.g, Equals(expected.g));
			AssertThat(result.b, Equals(expected.b));

			result = sdl_util::lerp(c1, c2, 0.0);
			expected = {255, 0, 0};
			AssertThat(result.r, Equals(expected.r));
			AssertThat(result.g, Equals(expected.g));
			AssertThat(result.b, Equals(expected.b));

			result = sdl_util::lerp(c1, c2, 1.0);
			expected = {0, 255, 0};
			AssertThat(result.r, Equals(expected.r));
			AssertThat(result.g, Equals(expected.g));
			AssertThat(result.b, Equals(expected.b));
		});
	});
});

#endif
