#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "GL.h"
#include "GLFW/glfw3.h"
#include "cglm/vec3.h"
#include "cglm/cam.h"
#include "camera.h"
#include "fps_cam_ctl.h"
#include "global.h"
#include "fixed_size_mem_pool.h"
#include "renderer.h"
#include "string.h"

    
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    global.keystate[key] = action;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

void allocator_test() {
	Index data[3];

	printf("===ALLOCATOR TEST===\n");

	printf("Initial state:\n");
	print_memory_cells(0, 5);

	data[0] = mem_pool_alloc();
	mem[data[0]].leaf.data[0] = 123;
	printf("Alloc:\n");
	print_memory_cells(0, 5);

	data[1] = mem_pool_alloc();
	mem[data[1]].leaf.data[0] = 727;
	printf("Alloc:\n");
	print_memory_cells(0, 5);

	data[2] = mem_pool_alloc();
	mem[data[2]].leaf.data[0] = 1337;
	printf("Alloc:\n");
	print_memory_cells(0, 5);

	mem_pool_free(data[0]);
	printf("Free:\n");
	print_memory_cells(0, 5);

	mem_pool_free(data[2]);
	printf("Free:\n");
	print_memory_cells(0, 5);

	data[2] = mem_pool_alloc();
	mem[data[2]].leaf.data[0] = 0xFF;
	printf("Alloc:\n");
	print_memory_cells(0, 5);
}

int main() {
	Camera camera;
	FPSCameraController camera_controller;
	GLFWwindow* window;

	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	window = glfwCreateWindow(1080, 720, "Window", NULL, NULL);
	assert(window);

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	loadGL();
	renderer_init();
	mem_pool_init();
	
	#if defined(DEBUG)
		allocator_test();
	#endif

	camera_init(&camera);
	glm_vec3_copy((vec3){6.f, 2.f, 2.f}, camera.pos);
	glm_vec3_copy((vec3){-6.f, -2.f, -2.f}, camera.dir);
	glm_vec3_normalize(camera.dir);
	
	renderer_set_camera(&camera);
	camera_update_proj(&camera);
	camera_update_viewproj(&camera);

	camera_controller.camera = &camera;
	camera_controller.speed = 1.0;
	camera_controller.sens = 1.0;
	
	while(!glfwWindowShouldClose(window)){
		global.frametime_info.time_last = global.frametime_info.time;
		global.frametime_info.time = glfwGetTime();
		global.frametime_info.delta_last = global.frametime_info.delta;
		global.frametime_info.delta = global.frametime_info.time - global.frametime_info.time_last;

		glfwPollEvents();
		fps_camera_controller_update(&camera_controller);
		camera_update_viewproj(&camera);
		renderer_update_camera();

		renderer_clear();
		for (i32 x = -15; x < 16; x++)
		for (i32 y = -15; y < 16; y++)
		for (i32 z = -15; z < 16; z++)
		if(x*x + y*y + z*z > 16*16) {
			mat4 transform = GLM_MAT4_IDENTITY_INIT;
			glm_translate(transform, (vec3){(f32)x, (f32)y, (f32)z});
			rederer_draw_cube(transform);
		}

		rederer_draw_cube_lines(GLM_MAT4_IDENTITY);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	renderer_destroy();
	return 0;
}
