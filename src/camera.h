#if !defined(CAMERA_H)
#define CAMERA_H

#include "cglm/vec3.h"
#include "cglm/quat.h"

typedef struct Camera {
    vec3 pos, dir;
    float nearZ, farZ, aspect, fov;
    mat4 view, proj, viewproj;
} Camera;

void camera_init(Camera*);
void camera_update_viewproj(Camera*);
void camera_update_proj(Camera*);

#endif // CAMERA_H
