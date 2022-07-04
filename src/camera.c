#include "camera.h"
#include "cglm/cam.h"

void camera_init(Camera* camera) {
    glm_vec3_zero(camera -> pos);
    glm_quat_identity(camera -> dir);
    camera -> nearZ = .1f;
    camera -> farZ = 50.f;
    camera -> fov = 80.f;
    camera -> aspect = 16.f / 9.f;
    
    camera_update_proj(camera);
    camera_update_viewproj(camera);
}

void camera_update_viewproj(Camera* camera) {
    glm_quat_look(camera -> pos, camera -> dir, camera -> view);
    glm_mat4_mul(camera -> proj, camera -> view, camera -> viewproj);
}

void camera_update_proj(Camera* camera) {
    glm_perspective(camera -> fov, camera -> aspect, camera -> nearZ, camera -> farZ, camera -> proj);
}