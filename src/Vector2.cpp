#include "Vector2.hpp"

Vector2::Vector2(float x, float y, float q)
:x(x), y(y), q(q) {

}

Vector2 Vector2::project() {
  return Vector2(x/q, y/q, 1);
}
