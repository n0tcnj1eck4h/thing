#include <stdio.h>
#include "GL.h"
#include "GLFW/glfw3.h"

extern unsigned char resources_basic_vert[];
extern unsigned int resources_basic_vert_len;

int main() {
	for(int i = 0; i < resources_basic_vert_len; i++){
		putchar(resources_basic_vert[i]);
	}
	
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(500, 500, "Window", NULL, NULL);

	glfwMakeContextCurrent(window);

	loadGL();

	// Compile and link shaders
	GLuint program = glCreateProgram();
	{
		GLuint frag, vert;
		vert = glCreateShader(GL_VERTEX_SHADER);
		frag = glCreateShader(GL_FRAGMENT_SHADER);
	}

	glClearColor(0.5, 1.0, 0.75, 1.0);
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	return 0;
}
