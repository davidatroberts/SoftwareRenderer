#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
  Vector2(float x=0, float y=0, float q=1);

  Vector2 project();

	Vector2 operator*(float scalar);
	Vector2 operator+(const Vector2& other);

  float x;
  float y;
  float q;
};

#endif
