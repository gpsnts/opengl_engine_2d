#include "headers/opengl_config_setup.hpp"

using namespace std;

#include <glm/glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "headers/coord.hpp"
#include "headers/triangle.hpp"

const char* APP_NAME = "OpenGL WIP GameSetup";
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	GameSetup::setup_opengl_glfw();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_NAME, NULL, NULL);

	if (!OpenGLConfigSetup::create_window(window)) return -1;
	
	OpenGLConfigSetup::set_callbacks_and_context(window);

	if (!OpenGLConfigSetup::init_glad()) return -1;

	Coord* top = new Coord((GLfloat) 0.0f, (GLfloat) 0.5f, (GLfloat)0.0f);
	Coord* left 	= new Coord(0.5f, -0.5f, 0.0f);
	Coord* right 	= new Coord(-0.5f, -0.5f, 0.0f);

	Triangle* triangle = new Triangle(top, left, right);

	triangle->data();

	while (!glfwWindowShouldClose(window))
	{
		// ! FPS Info
		GameSetup::frames_per_second(window);
		
		glfwPollEvents();
		glfwSwapBuffers(window);

		glClearColor(0.23f, 0.01f, 0.45f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glfwTerminate();
	return 0;
}
