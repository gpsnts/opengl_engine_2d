#include "../headers/triangle.hpp"

#include <iostream>

Triangle::Triangle(Coord* top, Coord* left, Coord* right)
{
	top_point = *top;
	left_point = *left;
	right_point = *right;
	
	GLfloat plot[] = {
		top_point.x, top_point.y, top_point.z,
		left_point.x, left_point.y, left_point.z,
		right_point.x, right_point.y, right_point.z
	};

	plot_triangle = plot;
	
	delete top, left, right;
}

Triangle::~Triangle()
{
	delete[] plot_triangle;
}

void Triangle::data()
{
	std::cout 
		<< "top "
		<< this->top_point.x
		<< " - "
		<< this->top_point.y
		<< " - "
		<< this->top_point.z
		<< " "
	<< std::endl;
	
	std::cout 
		<< "top "
		<< this->left_point.x
		<< " - "
		<< this->left_point.y
		<< " - "
		<< this->left_point.z
		<< " "
	<< std::endl;

	std::cout 
		<< "top "
		<< this->right_point.x
		<< " - "
		<< this->right_point.y
		<< " - "
		<< this->right_point.z
		<< " "
	<< std::endl;
	// std::cout << "plot_triangle[3] " << this->plot_triangle[3] << std::endl;
	// std::cout << "plot_triangle[4] " << this->plot_triangle[4] << std::endl;
	// std::cout << "plot_triangle[5] " << this->plot_triangle[5] << std::endl;
	// std::cout << "plot_triangle[6] " << this->plot_triangle[6] << std::endl;
	// std::cout << "plot_triangle[7] " << this->plot_triangle[7] << std::endl;
	// std::cout << "plot_triangle[8] " << this->plot_triangle[8] << std::endl;
	// std::cout << "plot_triangle[9] " << this->plot_triangle[9] << std::endl;	
	// std::cout << "top_point (x, y, z)" << this->top_point.x << this->top_point.y << this->top_point.z  << std::endl;
	// std::cout << "left_point (x, y, z)" << this->left_point.x << this->left_point.y << this->left_point.z  << std::endl;
	// std::cout << "right_point (x, y, z)" << this->right_point.x << this->right_point.y << this->right_point.z  << std::endl;
}