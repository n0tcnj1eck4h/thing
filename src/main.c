#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL.h"
#include "GLFW/glfw3.h"
#include "cglm/vec3.h"
#include "camera.h"

extern GLchar resources_vert_glsl[];
extern unsigned int resources_vert_glsl_len;

extern GLchar resources_frag_glsl[];
extern unsigned int resources_frag_glsl_len;

const vec3 vertices[] = {
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 1.0f},
};

const GLuint indices[] = {
	0, 2, 1,
	2, 3, 1,

	0, 4, 6,
	6, 2, 0,

	6, 7, 3,
	3, 2, 6,

	5, 1, 3,
	3, 7, 5,

	5, 4, 0,
	0, 1, 5,

	5, 7, 6,
	6, 4, 5
};

GLuint make_shader(GLenum type, const GLchar* source, int len) {
	GLuint shader;
	GLint compile_status, log_length;
	char* log;

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, &len);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

	if(!compile_status) {
		log = malloc(log_length);
		glGetShaderInfoLog(shader, log_length, NULL, log);
		printf("%s", log);

		free(log);
		assert(compile_status);
	}

	return shader;
}

GLuint make_program(const GLchar* vert_source, unsigned int vert_source_len, const GLchar* frag_source, unsigned int frag_source_len) {
	GLuint vert, frag, program;
	GLint link_status, log_length;
	char* log;

	program = glCreateProgram();
	vert = make_shader(GL_VERTEX_SHADER, resources_vert_glsl, resources_vert_glsl_len);
	frag = make_shader(GL_FRAGMENT_SHADER, resources_frag_glsl, resources_frag_glsl_len);

	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);

	glDeleteShader(vert);
	glDeleteShader(frag);

	glGetProgramiv(program, GL_LINK_STATUS, &link_status);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);

	if(!link_status) {
		log = malloc(log_length);
		glGetProgramInfoLog(program, log_length, NULL, log);
		printf("%s", log);

		free(log);
		assert(link_status);
	}
	return program;
}

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
         (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),    
		  type, severity, message);
}
    

int main() {
	GLuint program;
	GLFWwindow* window;
	GLuint VBO, IBO, VAO;

	glfwInit();

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	window = glfwCreateWindow(1080, 720, "Window", NULL, NULL);
	assert(window);

	glfwMakeContextCurrent(window);

	loadGL();

	#if defined(DEBUG)
		printf("Debug enabled!\n");
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback( MessageCallback, 0 );
	#endif // DEBUG

	program = make_program(resources_vert_glsl, resources_vert_glsl_len, resources_frag_glsl, resources_frag_glsl_len);
	glUseProgram(program);

	glCreateVertexArrays(1, &VAO);
	glCreateBuffers(1, &VBO);
	glCreateBuffers(1, &IBO);

	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(IBO, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(vec3));
	glVertexArrayElementBuffer(VAO, IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glViewport(0, 0, 1080, 720);
	glClearColor(0.5, 1.0, 0.75, 1.0);
	while(!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(*indices), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(program);
	return 0;
}
