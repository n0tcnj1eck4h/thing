#if !defined(RENDERER_H)
#define RENDERER_H

#include "GL.h"
#include "GLFW/glfw3.h"
#include "cglm/vec3.h"
#include "camera.h"

void renderer_init();
void renderer_render();
void renderer_set_camera(Camera* camera);
void renderer_destroy();

#endif // RENDERER_H
