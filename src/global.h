#if !defined(GLOBAL_H)
#define GLOBAL_H

#include "types.h"
#include "GLFW/glfw3.h"

struct {
    struct {
        f32 delta;
        f32 time;
        f32 delta_last;
        f32 time_last;
    } frametime_info;
    u8 keystate[GLFW_KEY_LAST];
} global = {0};


#endif // GLOBAL_H
