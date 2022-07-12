#if !defined(RENDERER_H)
#define RENDERER_H

#include "GL.h"
#include "GLFW/glfw3.h"
#include "cglm/vec3.h"
#include "camera.h"

void renderer_init();
void renderer_clear();
void renderer_update_camera();
void rederer_draw_cube(mat4 transform);
void renderer_set_camera(Camera* camera);
void renderer_destroy();

#endif // RENDERER_H
