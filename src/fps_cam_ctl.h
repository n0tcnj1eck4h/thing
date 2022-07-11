#if !defined(FPS_CAM_CTL_H)
#define FPS_CAM_CTL_H

#include "camera.h"

typedef struct FPSCameraController {
    Camera* camera;
    float speed;
    float sens;
} FPSCameraController;

void fps_camera_controller_update(FPSCameraController* controller);


#endif // FPS_CAM_CTL_H
