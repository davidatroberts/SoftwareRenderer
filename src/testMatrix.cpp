#ifndef TEST_MATRIX
#define TEST_MATRIX

#include "bandit/bandit.h"
#include "Matrix.hpp"
using namespace bandit;

go_bandit([]() {
	describe("Matrix<float> Tests", [&]() {
		it("correctly compares", [&]() {
			Matrix<float> m1;
			m1(0, 0) = 10.0f;
			Matrix<float> m2;

			AssertThat(false, Equals(m1==m2));
			AssertThat(true, Equals(m1!=m2));
		});

		it("uses identity", [&]() {
			Matrix<float> m1;

			Matrix<float> m2;
			m2(0, 0) = 1.0f;
			m2(1, 1) = 1.0f;
			m2(2, 2) = 1.0f;
			m2(3, 3) = 1.0f;
			m2(0, 1) = m2(0, 2) = m2(0, 3) = 0;
			m2(1, 0) = m2(1, 2) = m2(1, 3) = 0;
			m2(2, 0) = m2(2, 1) = m2(2, 3) = 0;
			m2(3, 0) = m2(3, 1) = m2(3, 2) = 0;

			AssertThat(true, Equals(m1==m2));
		});

		it("can translate", [&]() {
			Matrix<float> m1 = Matrix<float>::translate(1, 2, 3);

			Matrix<float> m2;
			m2(3, 0) = 1;
			m2(3, 1) = 2;
			m2(3, 2) = 3;
			m2(3, 3) = 1;

			AssertThat(true, Equals(m1==m2));
		});

		it("multiply with vector", [&]() {
			Matrix<float> m1;
			m1(0, 0) = 1;  m1(0, 1) = 2;  m1(0, 2) = 3;  m1(0, 3) = 4;
			m1(1, 0) = 5;  m1(1, 1) = 6;  m1(1, 2) = 7;  m1(1, 3) = 8;
			m1(2, 0) = 9;  m1(2, 1) = 10; m1(2, 2) = 11; m1(2, 3) = 12;
			m1(3, 0) = 13; m1(3, 1) = 14; m1(3, 2) = 15; m1(3, 3) = 16;

			Vector v(1, 2, 3, 4);
			Vector result = m1.mult_vector(v);

			Vector expected(51, 58, 65, 72);
			AssertThat(true, Equals(expected==result));
		});

		it("multiply with matrix", [&]() {
			Matrix<float> m1;
			m1(0, 0) = 1;  m1(0, 1) = 2;  m1(0, 2) = 3;  m1(0, 3) = 4;
			m1(1, 0) = 5;  m1(1, 1) = 6;  m1(1, 2) = 7;  m1(1, 3) = 8;
			m1(2, 0) = 9;  m1(2, 1) = 10; m1(2, 2) = 11; m1(2, 3) = 12;
			m1(3, 0) = 13; m1(3, 1) = 14; m1(3, 2) = 15; m1(3, 3) = 16;

			Matrix<float> m2;
			m2(0, 0) = 1; m2(0, 1) = 4; m2(0, 2) = 1; m2(0, 3) = 4;
			m2(1, 0) = 2; m2(1, 1) = 3; m2(1, 2) = 2; m2(1, 3) = 3;
			m2(2, 0) = 3; m2(2, 1) = 2; m2(2, 2) = 3; m2(2, 3) = 2;
			m2(3, 0) = 4; m2(3, 1) = 1; m2(3, 2) = 4; m2(3, 3) = 1;

			Matrix<float> result = m1*m2;

			Matrix<float> ex;
			ex(0, 0) = 30;  ex(0, 1) = 20;  ex(0, 2) = 30;  ex(0, 3) = 20;
			ex(1, 0) = 70;  ex(1, 1) = 60;  ex(1, 2) = 70;  ex(1, 3) = 60;
			ex(2, 0) = 110; ex(2, 1) = 100; ex(2, 2) = 110; ex(2, 3) = 100;
			ex(3, 0) = 150; ex(3, 1) = 140; ex(3, 2) = 150; ex(3, 3) = 140;
			AssertThat(true, Equals(ex==result));
		});

		it("translate vector", [&]() {
			Matrix<float> m = Matrix<float>::translate(5, 12, 3);
			Vector v(3, 2, 1, 1);
			Vector result = m.mult_vector(v);

			Vector expected(5+3, 12+2, 3+1, 1);
			AssertThat(true, Equals(expected==result));
		});

		it("rotatex vector", [&]() {
			Matrix<float> m = Matrix<float>::rotate_x(90);
			Vector v(0, 1, 0, 1);
			Vector result = m.mult_vector(v);

			Vector expected(0, 0, -1, 1);
			AssertThat(result.x, EqualsWithDelta(expected.x, 0.00001));
			AssertThat(result.y, EqualsWithDelta(expected.y, 0.00001));
			AssertThat(result.z, EqualsWithDelta(expected.z, 0.00001));
			AssertThat(result.w, EqualsWithDelta(expected.w, 0.00001));
		});

		it("rotatey vector", [&]() {
			Matrix<float> m = Matrix<float>::rotate_y(90);
			Vector v(0, 0, 1, 1);
			Vector result = m.mult_vector(v);

			Vector expected(-1, 0, 0, 1);
			AssertThat(result.x, EqualsWithDelta(expected.x, 0.00001));
			AssertThat(result.y, EqualsWithDelta(expected.y, 0.00001));
			AssertThat(result.z, EqualsWithDelta(expected.z, 0.00001));
			AssertThat(result.w, EqualsWithDelta(expected.w, 0.00001));
		});

		it("rotatez vector", [&]() {
			Matrix<float> m = Matrix<float>::rotate_z(90);
			Vector v(1, 0, 0, 1);
			Vector result = m.mult_vector(v);

			Vector expected(0, -1, 0, 1);
			AssertThat(result.x, EqualsWithDelta(expected.x, 0.00001));
			AssertThat(result.y, EqualsWithDelta(expected.y, 0.00001));
			AssertThat(result.z, EqualsWithDelta(expected.z, 0.00001));
			AssertThat(result.w, EqualsWithDelta(expected.w, 0.00001));
		});

		it("inverses", [&]() {
			Matrix<float> m;
			m(0, 0) = -4;
			m(0, 1) = m(0, 2) = m(0, 3) = 0;
			m(1, 0) = -1;
			m(1, 1) = 2;
			m(1, 2) = m(1, 3) = 0;
			m(2, 0) = -4;
			m(2, 1) = m(2, 2) = 4;
			m(2, 3) = 0;
			m(3, 0) = -1;
			m(3, 1) = -9;
			m(3, 2) = -1;
			m(3, 3) = 1;

			bool valid;
			Matrix<float> result =  m.inverse(valid);

			Matrix<float> expected;
			expected(0, 0) = -1.0f/4.0f;
			expected(1, 0) = -1.0f/8.0f;
			expected(1, 1) = 1.0f/2.0f;
			expected(2, 0) = -1.0f/8.0f;
			expected(2, 1) = -1.0f/2.0f;
			expected(2, 2) = 1.0f/4.0f;
			expected(3, 0) = -3.0f/2.0f;
			expected(3, 1) = 4.0f;
			expected(3, 2) = 1.0f/4.0f;
			expected(3, 3) = 1.0f;
			expected(0, 1) = expected(0, 2) = expected(0, 3) = 0; 
			expected(1, 2) = expected(1, 3) = 0;
			expected(2, 3) = 0;
			
			AssertThat(true, Equals(valid));
			AssertThat(true, Equals(expected==result));
		});

		it("transpose", [&]() {
			Matrix<float> m;
			m(0, 0) = 1;
			m(0, 1) = 2;
			m(0, 2) = 3;
			m(0, 3) = 4;
			m(1, 0) = 5;
			m(2, 0) = 6;
			m(3, 0) = 7;
			m(1, 1) = m(2, 2) = m(3, 3) = 0;

			Matrix<float> result = m.transpose();

			Matrix<float> expected;
			expected(0, 0) = 1;
			expected(1, 0) = 2;
			expected(2, 0) = 3;
			expected(3, 0) = 4;
			expected(0, 1) = 5;
			expected(0, 2) = 6;
			expected(0, 3) = 7;
			expected(1, 1) = expected(2, 2) = expected(3, 3) = 0;

			AssertThat(true, Equals(expected==result));
		});
	});
});

#endif