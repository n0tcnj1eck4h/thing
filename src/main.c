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

/*typedef struct {
	Index head;
	u64 depth;
} Octree;
*/

/*
void octree_draw(Index node_index, mat4 transform) {
	Block* block = &allocator.data[node_index];

	rederer_draw_cube_lines(transform);

	for(u8 i = 0; i < 8; i++) {
		if(block -> node.children[i] != 0) {
			mat4 transform_next;
			glm_mat4_copy(transform, transform_next);
			glm_scale_uni(transform_next, 0.5f);
			glm_translate(transform_next, (vec3){i & 1, (i >> 1) & 1, (i >> 2) & 1});
			octree_draw(block -> node.children[i], transform_next);
		}
	}
}

void octree_add_child(Index parent_index, u8 child_index) {
	Index child = allocator.data[parent_index].node.children[child_index];
	if(child) return;

	child = fsa_alloc(&allocator);
	allocator.data[child].leaf.data[0] = 0;
	allocator.data[child].leaf.data[1] = 0;
	allocator.data[parent_index].node.children[child_index] = child;
}

void octree_kill_children(Index parent) {
	Block* block = &allocator.data[parent];

	for(u8 i = 0; i < 8; i++) {
		if(block -> node.children[i] != 0) {
			octree_kill_children(block -> node.children[i]);
			fsa_free(&allocator, block -> node.children[i]);
			block -> node.children[i] = 0;
		}
	}
}
*/

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

	//Octree octree;

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
	fsa_init(&allocator);

	#if defined(DEBUG)
		fsa_test(&allocator);
		fsa_destroy(&allocator);
		fsa_init(&allocator);
	#endif // DEBUG

	// Reserve the first VOXEL_COUNT memory blocks for voxel info
	for (u32 i = 0; i < VOXEL_COUNT; i++) {
		fsa_alloc(&allocator);
	}

	fsa_print_cells(&allocator, VOXEL_COUNT - 4, 8);
	
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

	/*octree.head = fsa_alloc(&allocator);
	allocator.data[octree.head].leaf.data[0] = 0;
	allocator.data[octree.head].leaf.data[1] = 0;*/

	/*octree_add_child(octree.head, 6);
	octree_add_child(octree.head, 3);*/

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

		/*if(global.keystate[GLFW_KEY_R] == GLFW_PRESS) 
			octree_kill_children(octree.head);

		if(global.keystate[GLFW_KEY_E] == GLFW_PRESS)
			fsa_print_cells(&allocator, 0, 8);
			
		if(global.keystate[GLFW_KEY_1] == GLFW_PRESS)
			octree_add_child(octree.head, 0);
		if(global.keystate[GLFW_KEY_2] == GLFW_PRESS)
			octree_add_child(octree.head, 1);
		if(global.keystate[GLFW_KEY_3] == GLFW_PRESS)
			octree_add_child(octree.head, 2);
		if(global.keystate[GLFW_KEY_4] == GLFW_PRESS)
			octree_add_child(octree.head, 3);
		if(global.keystate[GLFW_KEY_5] == GLFW_PRESS)
			octree_add_child(octree.head, 4);
		if(global.keystate[GLFW_KEY_6] == GLFW_PRESS)
			octree_add_child(octree.head, 5);
		if(global.keystate[GLFW_KEY_7] == GLFW_PRESS)
			octree_add_child(octree.head, 6);
		if(global.keystate[GLFW_KEY_8] == GLFW_PRESS)
			octree_add_child(octree.head, 7);*/


			
		rederer_draw_cube_lines(GLM_MAT4_IDENTITY);
		//octree_draw(octree.head, GLM_MAT4_IDENTITY);

		glfwSwapBuffers(window);
	}

	fsa_destroy(&allocator);
	glfwDestroyWindow(window);
	renderer_destroy();
	return 0;
}
