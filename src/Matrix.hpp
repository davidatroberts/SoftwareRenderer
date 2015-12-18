#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <ostream>
#include <vector>
#include "Vector.hpp"

template<typename T>
class Matrix;

template<typename T>
bool operator==(Matrix<T> &m1, Matrix<T> &m2);

template<typename T>
bool operator!=(Matrix<T> &m1, Matrix<T> &m2);

template<typename T>
std::ostream& operator<<(std::ostream &strm, Matrix<T> &m);

template<typename T>
class Matrix {
public:
	Matrix();
	~Matrix();

	Vector mult_vector(Vector vec);
	Matrix<T> inverse();
	Matrix<T> inverse(bool &valid);
	Matrix<T> transpose();

	T& operator()(int x, int y);
	Matrix<T> operator*(Matrix<T>& other);

	static void transform_vertices(std::vector<Vector> &vectors, Matrix<T> &m);
	static Matrix<T> identity();
	static Matrix<T> translate(T x, T y, T z);
	static Matrix<T> rotate_x(T angle);
	static Matrix<T> rotate_y(T angle);
	static Matrix<T> rotate_z(T angle);
	static Matrix<T> perspective(T fov, T aspect_ratio, 
		T near, T far);
	static Matrix<T> scale(T x, T y, T z);
	static Matrix<T> lookat(Vector &eye, Vector &target, Vector &up);
		
	friend bool operator== <> (Matrix<T> &m1, Matrix<T> &m2);
	friend bool operator!= <> (Matrix<T> &m1, Matrix<T> &m2);
	friend std::ostream& operator<< <> (std::ostream &strm, Matrix<T> &m);

private:
	T values[4][4];
};

template<typename T>
Matrix<T>::Matrix() {
	values[0][0] = values[1][1] = values[2][2] = values[3][3] = 1;
	values[0][1] = values[0][2] = values[0][3] = 0;
	values[1][0] = values[1][2] = values[1][3] = 0;
	values[2][0] = values[2][1] = values[2][3] = 0;
	values[3][0] = values[3][1] = values[3][2] = 0;
}

template<typename T>
Matrix<T>::~Matrix() {

}

template<typename T>
Vector Matrix<T>::mult_vector(Vector vec) {
	Vector result;

	result.x = ((vec.x * values[0][0]) + (vec.y * values[1][0]) 
		+ (vec.z * values[2][0]) + values[3][0]);
	result.y = ((vec.x * values[0][1]) + (vec.y * values[1][1]) 
		+ (vec.z * values[2][1]) + values[3][1]);
	result.z = ((vec.x * values[0][2]) + (vec.y * values[1][2]) 
		+ (vec.z * values[2][2]) + values[3][2]);
	result.w = ((vec.x * values[0][3]) + (vec.y * values[1][3]) 
		+ (vec.z * values[2][3]) + values[3][3]);

	return result;	
}

template<typename T>
Matrix<T> Matrix<T>::inverse() {
	bool valid;
	return inverse(valid);
}

template<typename T>
Matrix<T> Matrix<T>::inverse(bool &valid) {
	Matrix<T> inv;

	inv(0, 0) = values[1][1] * values[2][2] * values[3][3] -
				values[1][1] * values[2][3] * values[3][2] -
				values[2][1] * values[1][2] * values[3][3] +
				values[2][1] * values[1][3] * values[3][2] +
				values[3][1] * values[1][2] * values[2][3] -
				values[3][1] * values[1][3] * values[2][2];

	inv(1, 0) = -values[1][0] * values[2][2] * values[3][3] +
				values[1][0] * values[2][3] * values[3][2] +
				values[2][0] * values[1][2] * values[3][3] -
				values[2][0] * values[1][3] * values[3][2] -
				values[3][0] * values[1][2] * values[2][3] +
				values[3][0] * values[1][3] * values[2][2];

	inv(2, 0) = values[1][0] * values[2][1] * values[3][3] -
				values[1][0] * values[2][3] * values[3][1] - 
				values[2][0] * values[1][1] * values[3][3] +
				values[2][0] * values[1][3] * values[3][1] +
				values[3][0] * values[1][1] * values[2][3] -
				values[3][0] * values[1][3] * values[2][1];

	inv(3, 0) = -values[1][0] * values[2][1] * values[3][2] +
				values[1][0] * values[2][2] * values[3][1] +
				values[2][0] * values[1][1] * values[3][2] - 
				values[2][0] * values[1][2] * values[3][1] -
				values[3][0] * values[1][1] * values[2][2] +
				values[3][0] * values[1][2] * values[2][1];

	inv(0, 1) = -values[0][1] * values[2][2] * values[3][3] +
				values[0][1] * values[2][3] * values[3][2] +
				values[2][1] * values[0][2] * values[3][3] -
				values[2][1] * values[0][3] * values[3][2] -
				values[3][1] * values[0][2] * values[2][3] +
				values[3][1] * values[0][3] * values[2][2];

	inv(1, 1) = values[0][0] * values[2][2] * values[3][3] -
				values[0][0] * values[2][3] * values[3][2] - 
				values[2][0] * values[0][2] * values[3][3] +
				values[2][0] * values[0][3] * values[3][2] +
				values[3][0] * values[0][2] * values[2][3] - 
				values[3][0] * values[0][3] * values[2][2];

	inv(2, 1) = -values[0][0] * values[2][1] * values[3][3] +
				values[0][0] * values[2][3] * values[3][1] +
				values[2][0] * values[0][1] * values[3][3] -
				values[2][0] * values[0][3] * values[3][1] -
				values[3][0] * values[0][1] * values[2][3] +
				values[3][0] * values[0][3] * values[2][1];

	inv(3, 1) = values[0][0] * values[2][1] * values[3][2] - 
				values[0][0] * values[2][2] * values[3][1] -
				values[2][0] * values[0][1] * values[3][2] +
				values[2][0] * values[0][2] * values[3][1] +
				values[3][0] * values[0][1] * values[2][2] -
				values[3][0] * values[0][2] * values[2][1];

	inv(0, 2) = values[0][1] * values[1][2] * values[3][3] - 
				values[0][1] * values[1][3] * values[3][2] - 
				values[1][1] * values[0][2] * values[3][3] +
				values[1][1] * values[0][3] * values[3][2] +
				values[3][1] * values[0][2] * values[1][3] -
				values[3][1] * values[0][3] * values[1][2];

	inv(1, 2) = -values[0][0] * values[1][2] * values[3][3] +
				values[0][0] * values[1][3] * values[3][2] +
				values[1][0] * values[0][2] * values[3][3] -
				values[1][0] * values[0][3] * values[3][2] -
				values[3][0] * values[0][2] * values[1][3] +
				values[3][0] * values[0][3] * values[1][2];

	inv(2, 2) = values[0][0] * values[1][1] * values[3][3] -
				values[0][0] * values[1][3] * values[3][1] -
				values[1][0] * values[0][1] * values[3][3] +
				values[1][0] * values[0][3] * values[3][1] +
				values[3][0] * values[0][1] * values[1][3] -
				values[3][0] * values[0][3] * values[1][1];

	inv(3, 2) = -values[0][0] * values[1][1] * values[3][2] +
				values[0][0] * values[1][2] * values[3][1] +
				values[1][0] * values[0][1] * values[3][2] -
				values[1][0] * values[0][2] * values[3][1] -
				values[3][0] * values[0][1] * values[1][2] +
				values[3][0] * values[0][2] * values[1][1];

	inv(0, 3) = -values[0][1] * values[1][2] * values[2][3] +
				values[0][1] * values[1][3] * values[2][2] +
				values[1][1] * values[0][2] * values[2][3] -
				values[1][1] * values[0][3] * values[2][2] -
				values[2][1] * values[0][2] * values[1][3] +
				values[2][1] * values[0][3] * values[1][2];

	inv(1, 3) = values[0][0] * values[1][2] * values[2][3] -
				values[0][0] * values[1][3] * values[2][2] - 
				values[1][0] * values[0][2] * values[2][3] +
				values[1][0] * values[0][3] * values[2][2] +
				values[2][0] * values[0][2] * values[1][3] -
				values[2][0] * values[0][3] * values[1][2];

	inv(2, 3) = -values[0][0] * values[1][1] * values[2][3] +
				values[0][0] * values[1][3] * values[2][1] +
				values[1][0] * values[0][1] * values[2][3] -
				values[1][0] * values[0][3] * values[2][1] -
				values[2][0] * values[0][1] * values[1][3] +
				values[2][0] * values[0][3] * values[1][1];

	inv(3, 3) = values[0][0] * values[1][1] * values[2][2] -
				values[0][0] * values[1][2] * values[2][1] -
				values[1][0] * values[0][1] * values[2][2] +
				values[1][0] * values[0][2] * values[2][1] +
				values[2][0] * values[0][1] * values[1][2] -
				values[2][0] * values[0][2] * values[1][1];

	T det = values[0][0] * inv(0, 0) + values[0][1] * inv(1, 0) +
		values[0][2] * inv(2, 0) + values[0][3] * inv(3, 0);

	if (det == 0) {
		valid = false;
		return inv;
	}
	valid = true;

	det = 1.0 / det;

	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			inv(i, j) = inv(i, j) * det;
		}
	}

	return inv;
}

template<typename T>
Matrix<T> Matrix<T>::transpose() {
	Matrix<T> m;

	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			m(i, j) = (*this)(j, i);
		}
	}

	return m;
}

template<typename T>
T& Matrix<T>::operator()(int x, int y) {
	return values[x][y];
}

template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& other) {
	Matrix<T> m;

	for (int i=0; i<4; ++i) {
		for (int j=0; j<4; ++j) {
			T sum = 0;
			for (int k=0; k<4; ++k) {
				sum += (values[i][k] * other(k, j));
			}
			m(i, j) = sum;
		}
	}

	return m;
}

template<typename T>
void Matrix<T>::transform_vertices(std::vector<Vector> &vertices, Matrix<T> &m) {
	for (int i=0; i<vertices.size(); ++i) {
		vertices[i] = m.mult_vector(vertices[i]);
	}
}

template<typename T>
Matrix<T> Matrix<T>::identity() {
	Matrix<T> m;
	return m;
}

template<typename T>
Matrix<T> Matrix<T>::translate(T x, T y, T z) {
	Matrix<T> m;
	m(3, 0) = x;
	m(3, 1) = y;
	m(3, 2) = z;
	return m;
}

template<typename T>
Matrix<T> Matrix<T>::rotate_x(T angle) {
	T rad = angle*M_PI/180.0f;
	
	Matrix<T> m;
	m(1, 1) = cos(rad);
	m(1, 2) = -sin(rad);
	m(2, 1) = sin(rad);
	m(2, 2) = cos(rad);
	return m;
}

template<typename T>
Matrix<T> Matrix<T>::rotate_y(T angle) {
	T rad = angle*M_PI/180.0f;

	Matrix<T> m;
	m(0, 0) = cos(rad);
	m(0, 2) = sin(rad);
	m(2, 0) = -sin(rad);
	m(2, 2) = cos(rad);
	return m;
}

template<typename T>
Matrix<T> Matrix<T>::rotate_z(T angle) {
	T rad = angle*M_PI/180.0f;

	Matrix<T> m;
	m(0, 0) = cos(rad);
	m(0, 1) = -sin(rad);
	m(1, 0) = sin(rad);
	m(1, 1) = cos(rad);
	return m;
}

template<typename T>
Matrix<T> Matrix<T>::perspective(T fov, T aspect_ratio, 
	T near, T far) {
	T t = 1.0f/tan(fov*0.5f);

	Matrix<T> m;
	m(0, 0) = t / aspect_ratio;
	m(1, 1) = t;
	m(2, 2) = -far/(near-far);
	m(2, 3) = 1;
	m(3, 2) = (near*far)/(near-far);
	m(3, 3) = 0;
	return m;
}

template<typename T>
Matrix<T>Matrix<T>::scale(T x, T y, T z) {
	Matrix<T> m;
	m(0, 0) = x;
	m(1, 1) = y;
	m(2, 2) = z;
	return m;
}

template<typename T>
Matrix<T> Matrix<T>::lookat(Vector &eye, Vector &target, Vector &up) {
	Vector z_axis = (target-eye).normalized();
	Vector x_axis = (up^z_axis).normalized();
	Vector y_axis = z_axis^x_axis;

	Matrix<T> m;
	m(0, 0) = x_axis.x;
	m(0, 1) = y_axis.x;
	m(0, 2) = z_axis.x;

	m(1, 0) = x_axis.y;
	m(1, 1) = y_axis.y;
	m(1, 2) = z_axis.y;

	m(2, 0) = x_axis.z;
	m(2, 1) = y_axis.z;
	m(2, 2) = z_axis.z;

	m(3, 0) = -(x_axis.dot(eye));
	m(3, 1) = -(y_axis.dot(eye));
	m(3, 2) = -(z_axis.dot(eye));

	return m;
}

template<typename T>
bool operator==(Matrix<T> &m1, Matrix<T> &m2) {
	return (
		m1(0, 0) == m2(0, 0) &&
		m1(0, 1) == m2(0, 1) &&
		m1(0, 2) == m2(0, 2) &&
		m1(0, 3) == m2(0, 3) &&
		m1(1, 0) == m2(1, 0) &&
		m1(1, 1) == m2(1, 1) &&
		m1(1, 2) == m2(1, 2) &&
		m1(1, 3) == m2(1, 3) &&
		m1(2, 0) == m2(2, 0) &&
		m1(2, 1) == m2(2, 1) &&
		m1(2, 2) == m2(2, 2) &&
		m1(2, 3) == m2(2, 3) &&
		m1(3, 0) == m2(3, 0) &&
		m1(3, 1) == m2(3, 1) &&
		m1(3, 2) == m2(3, 2) &&
		m1(3, 3) == m2(3, 3)
	);
}

template<typename T>
bool operator!=(Matrix<T> &m1, Matrix<T> &m2) {
	return !(m1==m2);
}

template<typename T>
std::ostream& operator<<(std::ostream &strm, Matrix<T> &m) {
	for (int i=0; i<4; ++i) {
		strm << "[" << m(i, 0) << ", " << m(i, 1) << ", " << m(i, 2)
			<< ", " << m(i, 3) << "]" << std::endl;
	}
	return strm;
}

#endif