#ifndef TEST_VECTOR
#define TEST_VECTOR

#include <vector>
#include "bandit/bandit.h"
#include "Vector.hpp"
using namespace bandit;

go_bandit([]() {
	describe("Vector Tests", [&]() {
		it("calculates magnitude", [&]() {
			Vector v1(3, 4, 0, 2);
			float result = v1.magnitude();

			float expected = 5;
			AssertThat(result, Equals(expected));
		});

		it("can normalize", [&]() {
			// Vector v1(3, 1, 2, 0);
			// Vector result = v1.normalized();

			// Vector expected(0.802f, 0.267f, 0.534f, 0);
			// AssertThat(result.x, Equals(expected.x));
			// AssertThat(result.y, Equals(expected.y));
			// AssertThat(result.z, Equals(expected.z));
			// AssertThat(result.w, Equals(expected.w));
		});

		it("can dot", [&]() {
			// Vector v1(1, 2, 3, 4);
			// Vector v2(4, 5, 6, 7);
			// float result = v1.dot(v2);

			// float expected = 60;
			// AssertThat(result, Equals(expected));
		});

		it("can add", [&]() {
			Vector v1(4, 5, 6, 7);
			Vector v2(8, 9, 10, 11);
			Vector result = v1+v2;

			Vector expected(12, 14, 16, 18);
			AssertThat(result.x, Equals(expected.x));
			AssertThat(result.y, Equals(expected.y));
			AssertThat(result.z, Equals(expected.z));
			AssertThat(result.w, Equals(expected.w));
		});

		it("can subtract", [&]() {
			Vector v1(11, 22, 33, 44);
			Vector v2(44, 33, 22, 11);
			Vector result = v1-v2;

			Vector expected(-33, -11, 11, 33);
			AssertThat(result.x, Equals(expected.x));
			AssertThat(result.y, Equals(expected.y));
			AssertThat(result.z, Equals(expected.z));
			AssertThat(result.w, Equals(expected.w));
		});

		it("can cross", [&]() {
			Vector v1(2, 3, 4, 1);
			Vector v2(5, 6, 7, 1);
			Vector result = v1^v2;

			Vector expected(-3, 6, -3, 1);
			AssertThat(result.x, Equals(expected.x));
			AssertThat(result.y, Equals(expected.y));
			AssertThat(result.z, Equals(expected.z));
			AssertThat(result.w, Equals(expected.w));
		});

		it("project 4D to 3D", [&]() {
			Vector v1(145, 574, 282, 8);
			Vector result = v1.project_to_3d();

			Vector expected(18.125, 71.75, 35.25, 1);
			AssertThat(result.x, Equals(expected.x));
			AssertThat(result.y, Equals(expected.y));
			AssertThat(result.z, Equals(expected.z));
			AssertThat(result.w, Equals(expected.w));
		});

		it("project multiple 4D to 3D", [&]() {
			std::vector<Vector> vertices = {
				Vector(10, 20, 30, 2)
			};
			Vector::project_to_3d(vertices);

			Vector expected(5, 10, 15, 1);

			AssertThat(vertices[0].x, Equals(expected.x));
			AssertThat(vertices[0].y, Equals(expected.y));
			AssertThat(vertices[0].z, Equals(expected.z));
			AssertThat(vertices[0].w, Equals(expected.w));
		});

		it("can reflect", [&]() {
			Vector normal(0, 1, 0);
			Vector v(1, 0, 0);

			Vector result = v.reflect(normal);
			std::cout << result << std::endl;
			
		});
	});
});

#endif