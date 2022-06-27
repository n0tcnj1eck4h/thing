#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL.h"
#include "GLFW/glfw3.h"

extern GLchar resources_vert_glsl[];
extern unsigned int resources_vert_glsl_len;

extern GLchar resources_frag_glsl[];
extern unsigned int resources_frag_glsl_len;

GLuint make_shader(GLenum type, const GLchar* source, int len) {
	GLuint shader;
	GLint compile_status, log_length;
	char* log;
	shader = glCreateShader(type);

	glShaderSource(shader, 1, &source, &len);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

	if(!compile_status) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
		log = malloc(log_length);

		glGetShaderInfoLog(shader, log_length, NULL, log);
		printf("%s", log);

		free(log);
		assert(0);
	}

	return shader;
}

int main() {
	glfwInit();

	GLFWwindow *window = glfwCreateWindow(500, 500, "Window", NULL, NULL);

	glfwMakeContextCurrent(window);

	loadGL();

	// Compile and link shaders
	GLuint program = glCreateProgram();
	glAttachShader(program, make_shader(GL_VERTEX_SHADER, resources_vert_glsl, resources_vert_glsl_len));
	glAttachShader(program, make_shader(GL_FRAGMENT_SHADER, resources_frag_glsl, resources_frag_glsl_len));

	glLinkProgram(program);
	glUseProgram(program);

	glClearColor(0.5, 1.0, 0.75, 1.0);
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	return 0;
}
