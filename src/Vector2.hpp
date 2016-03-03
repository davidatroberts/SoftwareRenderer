#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
  Vector2(float x=0, float y=0, float q=1);

  Vector2 project();

  float x;
  float y;
  float q;
};

#endif
