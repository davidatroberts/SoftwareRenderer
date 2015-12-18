#ifndef DEBUG_H
#define DEBUG_H 

#include <ostream>
#include <vector>
#include "Graphics.hpp"
#include "Vector.hpp"

namespace debug {
	void output(Vector vector, std::ostream &stream);
	void output(std::vector<Triangle> triangles, std::ostream &stream);
	void output(std::vector<Vector> vectors, std::ostream &stream);
	void print(std::vector<Triangle> triangles);
	void print(std::vector<Vector> vectors);
	void log(Vector vector);
	void log(std::vector<Triangle> triangles);
	void log(std::vector<Vector> vectors);
	void log(std::string msg);
}

#endif