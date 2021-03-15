// ! STEPS CREATING SHADERS
/**
 * 1. Crete Vertex Shader
 * 2. Create Fragment Shader
 * 3. Compile the shaders
 * 4. Create shader program
 * 5. Attach shader to the program
 * 6. Link compiled shaders into a program (single)
*/
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

// TODO: Botar em arquivos
const GLchar* vertexShader =
"#version 450\n"
"layout (location = 0) in vec3 pos;\n" // location = 0 --> glVertexAttribPoint (first) 0
"void main()\n"
"{\n"
"		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);" // Output shader
"}\n";

const GLchar* fragShader =
"#version 450\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
" 	color = vec4(0.35f, 0.96f, 0.31f, 1.0f);"
"}\n";

int main()
{
	GameSetup::setup_opengl_glfw();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, APP_NAME, NULL, NULL);

	if (!OpenGLConfigSetup::create_window(window)) return -1;
	
	OpenGLConfigSetup::set_callbacks_and_context(window);

	if (!OpenGLConfigSetup::init_glad()) return -1;

	Coord* top 		= new Coord(0.0f, 0.5f, 0.0f);
	Coord* left 	= new Coord(0.5f, -0.5f, 0.0f);
	Coord* right 	= new Coord(-0.5f, -0.5f, 0.0f);

	Triangle* triangle = new Triangle(top, left, right);

	// VBO - "GPU Object". The way which GPU understans data. Used to save and reduce GPU->CPU time consuming consults
	GLuint vao, vbo;

	GLfloat p_plot[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f		
	};

	// glGenBuffers - creates a chunk of mem in GPU: buffer objects 
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // Set VBO as the "current buffer". OpenGL only accepts a buffer per time
	glBufferData(GL_ARRAY_BUFFER, sizeof(p_plot), p_plot, GL_STATIC_DRAW);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(triangle->plot_triangle), triangle->plot_triangle, GL_STATIC_DRAW);
	
	/** 
	 * glBufferData
	 * Sets data to the buffer (vbo)
	 * first param: Type of data
	 * second param: size of data
	 * third param: data itself
	 * fourth param: type of data
	 * 	types::
	 * 		GL_STREAM_DRAW = Create once, set once, use once
	 * 		GL_STATIC_DRAW =  Create once, set once, use a lot 
	 * 		GL_DYNAMIC_DRAW = Create once, change a lot, use a lot
	*/

	// VAO - Hold info for a buffer - as color, texture e.g

	glGenVertexArrays(1, &vao); // Create VAO
	glBindVertexArray(vao); // Binds VAO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// 1º offset init 2º offset final  3º type of data
	// 4º normalized 5º stride num of bytes beetween for e.g the 0 and 3 points 
	// 6º offset first component (beginning == NULL)

	glEnableVertexArrayAttrib(vao, 0); // Enable VAO

	// Creting Vert Shader
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertexShader, NULL); // Shader id, quantity, definition, lenght
	glCompileShader(vertex_shader);

	// Check Errors
	GLint result;
	GLchar log[512];

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(vertex_shader, sizeof(log), NULL, log);
		cerr << "ERROR (vertex_shader) -- " << log << " " << endl;
		return -1;
	}

	GLuint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_shader, 1, &fragShader, NULL);
	glCompileShader(frag_shader);

	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(frag_shader, sizeof(log), NULL, log);
		cerr << "ERROR (frag_shader) -- " << log << " " << endl;
		return -1;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, frag_shader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(log), NULL, log);
		cerr << "ERROR (program) -- " << log << " " << endl;
		return -1;
	}
	
	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);

	while (!glfwWindowShouldClose(window))
	{
		// ! FPS Info
		GameSetup::frames_per_second(window);
		
		glfwPollEvents();
		glfwSwapBuffers(window);

		glUseProgram(program);
		glBindVertexArray(vao); // "uses" vao
		glDrawArrays(GL_TRIANGLES, 0, 3); // Type of Draw primitive, which component start, num of vertices
		glBindVertexArray(0); // "removes" vao

		glClearColor(0.05f, 0.01f, 0.22f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	glfwTerminate();
	return 0;
}
