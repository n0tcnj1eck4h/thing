#include "fps_cam_ctl.h"
#include "GLFW/glfw3.h"
#include "types.h"
#include "global.h"

static u8 key_pressed(u16 key) {
	return global.keystate[key] != GLFW_RELEASE;
} 

void fps_camera_controller_update(FPSCameraController* controller) {
    float delta = global.frametime_info.delta;
    float speed = controller -> speed;
    float distance = speed * delta;
    vec3 movement = GLM_VEC3_ZERO_INIT;
    vec3 right;

    if(key_pressed(GLFW_KEY_LEFT)) {
        glm_vec3_rotate(controller -> camera -> dir, -delta, GLM_YUP);
    }    

    if(key_pressed(GLFW_KEY_RIGHT)) {
        glm_vec3_rotate(controller -> camera -> dir, delta, GLM_YUP);
    }   


    glm_vec3_cross(GLM_YUP, controller -> camera -> dir, right);

    if(key_pressed(GLFW_KEY_DOWN)) {
        glm_vec3_rotate(controller -> camera -> dir, -delta, right);
    }   

    if(key_pressed(GLFW_KEY_UP)) {
        glm_vec3_rotate(controller -> camera -> dir, delta, right);
    }  


    if(key_pressed(GLFW_KEY_LEFT_SHIFT))
        distance *= 2.0;

    if(key_pressed(GLFW_KEY_W) ^ key_pressed(GLFW_KEY_S)) {
        glm_vec3_copy(controller -> camera -> dir, movement);
        movement[1] = 0.0;
        glm_vec3_normalize(movement);

        if(key_pressed(GLFW_KEY_S))
            glm_vec3_scale(movement, -1, movement);
    }

    if(key_pressed(GLFW_KEY_A) ^ key_pressed(GLFW_KEY_D)) {
        if(key_pressed(GLFW_KEY_A))
            glm_vec3_scale(right, -1, right);

        glm_vec3_add(movement, right, movement);
    }

    if(key_pressed(GLFW_KEY_SPACE)) {
        movement[1] -= 1.0;

    }
    if(key_pressed(GLFW_KEY_LEFT_CONTROL)) {
        movement[1] += 1.0;
    }

    glm_normalize(movement);
    glm_vec3_scale(movement, distance, movement);

    glm_vec3_add(controller -> camera -> pos, movement, controller -> camera -> pos);
}