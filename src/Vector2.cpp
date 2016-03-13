#include "Vector2.hpp"

Vector2::Vector2(float x, float y, float q)
:x(x), y(y), q(q) {

}

Vector2 Vector2::project() {
  return Vector2(x/q, y/q, 1);
}

Vector2 Vector2::operator*(float scalar) {
	return Vector2(x*scalar, y*scalar, q*scalar);
}

Vector2 Vector2::operator+(const Vector2& other) {
	return Vector2(x+other.x, y+other.y, q+other.q);
}
