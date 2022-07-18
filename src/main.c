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
#include "fsa.h"
#include "renderer.h"
#include "string.h"
#include "math.h"
#include "octree.h"

float clamp(float x, float upper, float lower) {
    return fmin(upper, fmax(x, lower));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    global.keystate[key] = action;
}

int main() {
	FPSCameraController camera_controller;
	FixedSizeAllocator allocator;
	GLFWwindow* window;
	Camera camera;
	Octree octree;

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
	renderer_set_draw_color(GLM_VEC3_ZERO);
	fsa_init(&allocator);

	for (size_t i = 0; i < VOXEL_COUNT; i++) {
		glm_vec3_copy((vec3){
			(i % 16) / 16.0,
			(i / 16 % 16) / 16.0,
			(i / 16 / 16 % 16) / 16.0
		}, global.palette[i]);
	}
	
	#if defined(DEBUG) && 0
		fsa_test(&allocator);
		fsa_destroy(&allocator);
		fsa_init(&allocator);
	#endif // DEBUG

	octree_init(&octree, &allocator);
	octree.reserved_indices = VOXEL_COUNT;

	octree_set_block(&octree, octree.head, 0b000, 0, 1000);
	octree_set_block(&octree, octree.head, 0b001, 0, 1000);
	octree_set_block(&octree, octree.head, 0b100, 0, 1000);
	octree_set_block(&octree, octree.head, 0b101, 0, 1000);

	octree_set_block(&octree, octree.head, 0b111000, 1, 0);
	octree_set_block(&octree, octree.head, 0b110001, 1, 0);
	octree_set_block(&octree, octree.head, 0b011100, 1, 0);
	octree_set_block(&octree, octree.head, 0b010101, 1, 0);

	octree_set_block(&octree, octree.head, 0b101000, 1, 255);
	octree_set_block(&octree, octree.head, 0b100001, 1, 255);
	octree_set_block(&octree, octree.head, 0b001100, 1, 255);
	octree_set_block(&octree, octree.head, 0b000101, 1, 255);

	camera_init(&camera);
	glm_vec3_copy((vec3){0.5f, 0.5f, 0.5f}, camera.pos);
	glm_vec3_copy(GLM_FORWARD, camera.dir);
	
	renderer_set_camera(&camera);
	camera_update_proj(&camera);
	camera_update_viewproj(&camera);

	camera_controller.camera = &camera;
	camera_controller.speed = 0.5;
	camera_controller.sens = 4.0;

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
		
		if(global.keystate[GLFW_KEY_ESCAPE] == GLFW_PRESS) 
			glfwSetWindowShouldClose(window, 1);

		//rederer_draw_cube_lines(GLM_MAT4_IDENTITY);
		
		renderer_set_draw_color(GLM_VEC3_ZERO);
		octree_draw(&octree, octree.head, GLM_MAT4_IDENTITY);

		glfwSwapBuffers(window);
	}

	fsa_destroy(&allocator);
	glfwDestroyWindow(window);
	renderer_destroy();
	return 0;
}
