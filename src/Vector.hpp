#ifndef VECTOR_H
#define VECTOR_H

#include <ostream>
#include <vector>

class Vector {
public:
	Vector(float x=0, float y=0, float z=0, float w=1);

	float p_norm(float p);
	float magnitude();
	float dot(Vector &other);
	Vector normalized();
	Vector project_to_3d();
	Vector reflect(Vector &normal);			// reflect vector around normal

	Vector operator*(float scalar);			// scalar multiplication
	Vector operator/(float scalar);			// scalar division
	Vector operator*(const Vector& vec);	// element-wise multiplication
	Vector operator+(const Vector& vec); 	// addition
	Vector operator-(const Vector& vec); 	// subtraction
	Vector operator^(const Vector& vec);	// cross
	Vector& operator+=(const Vector& vec);	// assign addition
	Vector& operator-=(const Vector& vec);	// assign subtraction

	static void project_to_3d(std::vector<Vector> &vertices);
	static void normalize(std::vector<Vector> &vectors);
	static Vector plane_normal(Vector &v1, Vector &v2, Vector &v3);
	static Vector lerp(Vector v1, Vector v2, float alpha);
	static Vector up();
	static Vector down();
	static Vector left();
	static Vector right();
	static Vector backward();
	static Vector forward();

	friend Vector operator-(const Vector &vec);
	friend bool operator==(Vector &v1, Vector &v2);
	friend bool operator!=(Vector &v1, Vector &v2);
	friend std::ostream& operator<<(std::ostream &strm, Vector &v);

	float x;
	float y;
	float z;
	float w;
};

#endif