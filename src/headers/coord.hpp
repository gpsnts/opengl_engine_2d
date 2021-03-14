#ifndef COORD_HPP_
#define COORD_HPP_

// #include "../pch/opengl_libs.hpp"
#include <GLFW/glfw3.h>

class Coord
{
	public:
		GLfloat x, y, z;
		Coord() {};
		Coord(GLfloat point_x, GLfloat point_y, GLfloat point_z);
};

#endif // !COORD_HPP_