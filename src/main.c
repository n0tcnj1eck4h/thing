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

float clamp(float x, float upper, float lower)
{
    return fmin(upper, fmax(x, lower));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    global.keystate[key] = action;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}


int main() {
	FPSCameraController camera_controller;
	FixedSizeAllocator allocator;
	GLFWwindow* window;
	Camera camera;

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
		/*for (i32 x = -15; x < 16; x++)
		for (i32 y = -15; y < 16; y++)
		for (i32 z = -15; z < 16; z++)
		if(x*x + y*y + z*z > 16*16) {
			mat4 transform = GLM_MAT4_IDENTITY_INIT;
			glm_translate(transform, (vec3){(f32)x, (f32)y, (f32)z});
			rederer_draw_cube(transform);
		}*/

		for (int i = 0; i < 64; i++) {
			mat4 transform = GLM_MAT4_IDENTITY_INIT;
			float rot = fmod(global.frametime_info.time - (i / 64.0), GLM_PI * 2.0 * 3.0);
			float rotx = clamp(rot, GLM_PI * 1.0, GLM_PI * 0.0) + clamp(rot, GLM_PI * 4.0, GLM_PI * 3.0);
			float roty = clamp(rot, GLM_PI * 2.0, GLM_PI * 1.0) + clamp(rot, GLM_PI * 5.0, GLM_PI * 4.0);
			float rotz = clamp(rot, GLM_PI * 3.0, GLM_PI * 2.0) + clamp(rot, GLM_PI * 6.0, GLM_PI * 5.0);

			glm_rotate(transform, rotx, GLM_XUP);
			glm_rotate(transform, roty, GLM_YUP);
			glm_rotate(transform, rotz, GLM_ZUP);

			glm_scale_uni(transform, 1.0 - i / 64.0);
			glm_translate(transform, (vec3){-0.5f, -0.5f, -0.5f});
			rederer_draw_cube_lines(transform);
		}
		
		//rederer_draw_cube_lines(GLM_MAT4_IDENTITY);

		glfwSwapBuffers(window);
	}

	fsa_destroy(&allocator);
	glfwDestroyWindow(window);
	renderer_destroy();
	return 0;
}
