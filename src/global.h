#if !defined(GLOBAL_H)
#define GLOBAL_H

#include "types.h"
#include "GLFW/glfw3.h"

typedef struct Global {
    struct {
        f32 delta;
        f32 time;
        f32 delta_last;
        f32 time_last;
    } frametime_info;
    u8 keystate[GLFW_KEY_LAST];
} Global;

extern Global global;

#endif // GLOBAL_H
