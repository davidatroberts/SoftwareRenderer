#ifndef TEST_GRAPHICS
#define TEST_GRAPHICS

#include "bandit/bandit.h"
#include "Graphics.hpp"
using namespace bandit;

go_bandit([]() {
	describe("Graphics Tests", [&]() {
		it("can sort points", [&]() {
			Fragment p1 = {0, 1, 0};
			Fragment p2 = {0, 2, 0};
			Fragment p3 = {0, 3, 0};
			Graphics::sort_points(p1, p2, p3);

			Fragment exp_p1 = {0, 1, 0};
			Fragment exp_p2 = {0, 2, 0};
			Fragment exp_p3 = {0, 3, 0};

			AssertThat(p1.y, Equals(exp_p1.y));
			AssertThat(p2.y, Equals(exp_p2.y));
			AssertThat(p3.y, Equals(exp_p3.y));

			p1 = {0, 3, 0};
			p2 = {0, 2, 0};
			p3 = {0, 1, 0};
			Graphics::sort_points(p1, p2, p3);

			AssertThat(p1.y, Equals(exp_p1.y));
			AssertThat(p2.y, Equals(exp_p2.y));
			AssertThat(p3.y, Equals(exp_p3.y));

			p1 = {0, 2, 0};
			p2 = {0, 3, 0};
			p3 = {0, 1, 0};
			Graphics::sort_points(p1, p2, p3);

			AssertThat(p1.y, Equals(exp_p1.y));
			AssertThat(p2.y, Equals(exp_p2.y));
			AssertThat(p3.y, Equals(exp_p3.y));

			p1 = {0, 1, 0};
			p2 = {0, 3, 0};
			p3 = {0, 2, 0};
			Graphics::sort_points(p1, p2, p3);

			AssertThat(p1.y, Equals(exp_p1.y));
			AssertThat(p2.y, Equals(exp_p2.y));
			AssertThat(p3.y, Equals(exp_p3.y));

			p1 = {0, 2, 0};
			p2 = {0, 1, 0};
			p3 = {0, 3, 0};
			Graphics::sort_points(p1, p2, p3);

			AssertThat(p1.y, Equals(exp_p1.y));
			AssertThat(p2.y, Equals(exp_p2.y));
			AssertThat(p3.y, Equals(exp_p3.y));

			p1 = {0, 3, 0};
			p2 = {0, 1, 0};
			p3 = {0, 2, 0};
			Graphics::sort_points(p1, p2, p3);

			AssertThat(p1.y, Equals(exp_p1.y));
			AssertThat(p2.y, Equals(exp_p2.y));
			AssertThat(p3.y, Equals(exp_p3.y));
		});
	});
});

#endif