#pragma once
#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

// #include "../pch/opengl_libs.hpp"
#include "coord.hpp"

class Triangle
{
	private:
		Coord top_point, left_point, right_point;
	public:
		Triangle(Coord* top, Coord* left, Coord* right);
		~Triangle();

		void data();

		GLfloat* plot_triangle;
};

#endif // !TRIANGLE_HPP_