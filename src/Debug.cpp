#include "Debug.hpp"

#include <fstream>
#include <iostream>

void debug::output(Vector vector, std::ostream &stream) {
	stream << " x:" << vector.x << " y:" << vector.y << " z:" << vector.z
			<< " w:" << vector.w << std::endl;
}

void debug::output(std::vector<Triangle> triangles, std::ostream &stream) {
	stream << "size: " << triangles.size() << std::endl;
	for (unsigned int i=0; i<triangles.size(); ++i) {
		Triangle t = triangles[i];

		stream << i << " a:" << t.a << " b:" << t.b << " c:" 
			<< t.c << std::endl;
	}
	stream << std::endl;
}

void debug::output(std::vector<Vector> vectors, std::ostream &stream) {
	stream << "size: " << vectors.size() << std::endl;
	for (unsigned int i=0; i<vectors.size(); ++i) {
		Vector v = vectors[i];

		stream << i << " x:" << v.x << " y:" << v.y << " z:" << v.z
			<< " w:" << v.w << std::endl;
	}
	stream << std::endl;
}

void debug::print(std::vector<Triangle> triangles) {
	output(triangles, std::cout);
}

void debug::print(std::vector<Vector> vectors) {
	output(vectors, std::cout);
}

void debug::log(Vector vector) {
	std::ofstream file;
	file.open("log.txt", std::ios::out | std::ios::app);
	output(vector, file);
	file.close();
}

void debug::log(std::vector<Triangle> triangles) {
	std::ofstream file;
	file.open("log.txt", std::ios::out | std::ios::app);
	output(triangles, file);
	file.close();
}

void debug::log(std::vector<Vector> vectors) {
	std::ofstream file;
	file.open("log.txt", std::ios::out | std::ios::app);
	output(vectors, file);
	file.close();
}

void debug::log(std::string msg) {
	std::ofstream file;
	file.open("log.txt", std::ios::out | std::ios::app);
	file << msg << std::endl;
	file.close();
}