#ifndef TEST_VECTOR2
#define TEST_VECTOR2

#include "bandit/bandit.h"
#include "Vector2.hpp"
using namespace bandit;

go_bandit([]() {
	describe("Vector2 Tests", [&]() {
		it("can add", [&]() {
			Vector2 v1(1, 2, 3);
			Vector2 v2(4, 5, 6);
			Vector2 result = v1+v2;

			Vector2 expected(5, 7, 9);
			AssertThat(result.x, Equals(expected.x));
			AssertThat(result.y, Equals(expected.y));
			AssertThat(result.q, Equals(expected.q));
		});

		it("can multiply by scalar", [&]() {
			Vector2 v1(4, 5, 6);
			Vector2 result = v1*5;

			Vector2 expected(20, 25, 30);
			AssertThat(result.x, Equals(expected.x));
			AssertThat(result.y, Equals(expected.y));
			AssertThat(result.q, Equals(expected.q));
		});
	});
});

#endif
