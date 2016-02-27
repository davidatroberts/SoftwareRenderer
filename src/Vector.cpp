#include "Vector.hpp"

#include <cmath>
#include <utility>

Vector::Vector(float x, float y, float z, float w)
: x(x), y(y), z(z), w(w) {

}

float Vector::p_norm(float p) {
	float xx = pow(x, p);
	float yy = pow(y, p);
	float zz = pow(z, p);

	float sqr = xx+yy+zz;
	return pow(sqr, 1.0f/p);
}

float Vector::magnitude() {
	return p_norm(2);
}

float Vector::dot(Vector &other) {
	float xx = x * other.x;
	float yy = y * other.y;
	float zz = z * other.z;

	return xx+yy+zz;
}

Vector Vector::normalized() {
	float m = magnitude();
	return (*this) * (1.0f/m);
}

Vector Vector::project_to_3d() {
	return Vector(x/w, y/w, z/w, 1);
}

Vector Vector::reflect(Vector &normal) {
	float d = normal.dot(*this);

	Vector v;
	v.x = x - 2.0f * d * normal.x;
	v.y = y - 2.0f * d * normal.y;
	v.z = z - 2.0f * d * normal.z;

	return v;
}

Vector Vector::operator*(float scalar) {
	float xx = x * scalar;
	float yy = y * scalar;
	float zz = z * scalar;
	float ww = w * scalar;

	return Vector(xx, yy, zz, ww);
}

Vector Vector::operator/(float scalar) {
	float xx = x / scalar;
	float yy = y / scalar;
	float zz = z / scalar;
	float ww = w / scalar;

	return Vector(xx, yy, zz, ww);
}

Vector Vector::operator*(const Vector &other) {
	return Vector(x*other.x, y*other.y, z*other.z, w*other.w);
}

Vector Vector::operator+(const Vector& other) {
	return Vector(x+other.x, y+other.y, z+other.z, w+other.w);
}

Vector Vector::operator-(const Vector& other) {
	return Vector(x-other.x, y-other.y, z-other.z, w-other.w);
}

Vector Vector::operator^(const Vector& other) {
	Vector v;
	v.x = y * other.z - z * other.y;
	v.y = z * other.x - x * other.z;
	v.z = x * other.y - y * other.x;
	return v;
}

Vector& Vector::operator+=(const Vector& other) {
	x+=other.x;
	y+=other.y;
	z+=other.z;
	w+=other.w;
	return *this;
}

Vector& Vector::operator-=(const Vector& other) {
	x-=other.x;
	y-=other.y;
	z-=other.z;
	w-=other.w;
	return *this;
}

Vector& Vector::operator=(Vector other) {
	std::swap(x, other.x);
	std::swap(y, other.y);
	std::swap(z, other.z);
	std::swap(w, other.w);
	return *this;
}

void Vector::project_to_3d(std::vector<Vector> &vertices) {
	for (int i=0; i<vertices.size(); ++i) {
		vertices[i] = vertices[i].project_to_3d();
	}
}

void Vector::normalize(std::vector<Vector> &vertices) {
	for (int i=0; i<vertices.size(); i++) {
		vertices[i] = vertices[i].normalized();
	}
}

Vector Vector::plane_normal(Vector &v1, Vector &v2, Vector &v3) {
	Vector e3 = v2 - v1;
	Vector e1 = v3 - v2;

	return (e3^e1) / (e3^e1).magnitude();
}

Vector Vector::lerp(Vector v1, Vector v2, float alpha) {
	return v1*(1-alpha) + v2*alpha;
}

Vector Vector::up() {
	return Vector(0, 1, 0);
}

Vector Vector::down() {
	return Vector(0, -1, 0);
}

Vector Vector::left() {
	return Vector(-1, 0, 0);
}

Vector Vector::right() {
	return Vector(1, 0, 0);
}

Vector Vector::forward() {
	return Vector(0, 0, 1);
}

Vector Vector::backward() {
	return Vector(0, 0, -1);
}

Vector operator-(const Vector &vec) {
	return Vector(-vec.x, -vec.y, -vec.z, -vec.w);
}

bool operator==(Vector &v1, Vector &v2) {
	return (
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z &&
		v1.w == v2.w);
}

bool operator!=(Vector &v1, Vector &v2) {
	return !(v1==v2);
}

std::ostream& operator<<(std::ostream &strm, Vector &v) {
	strm << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return strm;
}
