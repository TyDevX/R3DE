#include <stdio.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/threadmgr.h>
#include <vita2d.h>
#include <vitaGL.h>
#include <math.h>
#include <input.h>
//#include "shadershandler.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544
#define PI 3.14159265

float angle = 0.0;

void draw_cube() {
    vita2d_start_drawing();
    vita2d_clear_screen();
    vitaGL_clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    set_ps1_shader();

    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(angle, 1.0, 1.0, 1.0);  
    vitaGL_draw_cube_wireframe(2.0);

    angle += 1.0;

    unset_ps1_shader();

    vita2d_end_drawing();
    vita2d_swap_buffers();
}

int main(int argc, char* argv[]) {
    vita2d_init();
    vitaGL_init();
    vitaGL_set_clear_color(0, 0, 0, 255);

    if (load_shaders() < 0) {
        printf("Failed to load shaders.\n");
        return -1;
    }

    while (1) {
        draw_cube();
    }

    //cleanup_shaders();

    vitaGL_end();
    vita2d_fini();
    return 0;
}
