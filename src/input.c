#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <math.h>

#define MAX_ANALOG_VALUE 128
#define TOUCH_SENSITIVITY 0.005f

static SceCtrlData ctrl;
static SceTouchData touch;
static float camera_pos_x = 0.0f;
static float camera_pos_y = 0.0f;
static float camera_pos_z = 5.0f;
static float camera_rot_x = 0.0f;
static float camera_rot_y = 0.0f;

void handle_input() {
    sceCtrlPeekBufferPositive(0, &ctrl, 1);
    sceTouchPeek(0, &touch, 1);

    if (ctrl.rx > MAX_ANALOG_VALUE / 2) {
        camera_rot_y -= (ctrl.rx - MAX_ANALOG_VALUE / 2) / 1000.0f;
    } else if (ctrl.rx < MAX_ANALOG_VALUE / 2) {
        camera_rot_y += (MAX_ANALOG_VALUE / 2 - ctrl.rx) / 1000.0f;
    }

    if (ctrl.ry > MAX_ANALOG_VALUE / 2) {
        camera_rot_x -= (ctrl.ry - MAX_ANALOG_VALUE / 2) / 1000.0f;
    } else if (ctrl.ry < MAX_ANALOG_VALUE / 2) {
        camera_rot_x += (MAX_ANALOG_VALUE / 2 - ctrl.ry) / 1000.0f;
    }

    if (touch.reportNum > 0) {
        camera_pos_x += touch.report[0].x * TOUCH_SENSITIVITY;
        camera_pos_y -= touch.report[0].y * TOUCH_SENSITIVITY;
    }

    if (ctrl.lx > MAX_ANALOG_VALUE / 2) {
        camera_pos_x += sin(camera_rot_y) * 0.1f;
        camera_pos_z -= cos(camera_rot_y) * 0.1f;
    } else if (ctrl.lx < MAX_ANALOG_VALUE / 2) {
        camera_pos_x -= sin(camera_rot_y) * 0.1f;
        camera_pos_z += cos(camera_rot_y) * 0.1f;
    }

    if (ctrl.ly > MAX_ANALOG_VALUE / 2) {
        camera_pos_x -= sin(camera_rot_x) * cos(camera_rot_y) * 0.1f;
        camera_pos_y -= cos(camera_rot_x) * 0.1f;
        camera_pos_z -= sin(camera_rot_x) * sin(camera_rot_y) * 0.1f;
    } else if (ctrl.ly < MAX_ANALOG_VALUE / 2) {
        camera_pos_x += sin(camera_rot_x) * cos(camera_rot_y) * 0.1f;
        camera_pos_y += cos(camera_rot_x) * 0.1f;
        camera_pos_z += sin(camera_rot_x) * sin(camera_rot_y) * 0.1f;
    }
}

float get_camera_pos_x() {
    return camera_pos_x;
}

float get_camera_pos_y() {
    return camera_pos_y;
}

float get_camera_pos_z() {
    return camera_pos_z;
}

float get_camera_rot_x() {
    return camera_rot_x;
}

float get_camera_rot_y() {
    return camera_rot_y;
}
