#include <stdio.h>
#include "GL.h"
#include "GLFW/glfw3.h"

int main() {
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(500, 500, "Window", NULL, NULL);

	glfwMakeContextCurrent(window);

	loadGL();

	glClearColor(0.5, 1.0, 0.75, 1.0);
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	return 0;
}
