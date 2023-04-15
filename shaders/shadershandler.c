#include <stdio.h>
#include <string.h>
#include <psp2/gxm.h>
#include <vitaGL.h>

#define SHADER_COUNT 2

static const char *shader_filenames[SHADER_COUNT] = {
    "shaders/ps1shader.vcg",
    "shaders/ps1shader.fcg",
};

static const SceGxmProgram *shaders[SHADER_COUNT];

int load_shaders(void) {
    int i;
    for (i = 0; i < SHADER_COUNT; i++) {
        FILE *file = fopen(shader_filenames[i], "rb");
        if (!file) {
            printf("Failed to open shader file: %s\n", shader_filenames[i]);
            return -1;
        }

        fseek(file, 0, SEEK_END);
        const long pos = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *buf = (char*)malloc(pos + 1);
        memset(buf, 0, pos + 1);
        fread(buf, 1, pos, file);
        fclose(file);

        SceGxmShaderPatcherId shader_id;
        sceGxmShaderPatcherRegisterProgram(shader_patcher,
                                            buf,
                                            &shaders[i],
                                            &shader_id);
        free(buf);
    }
    return 0;
}

void set_ps1_shader(void) {
    vitaGLUniform1i(vitaGLGetUniformLocation(shaders[1], "ps1_shader"), 1);
}

void unset_ps1_shader(void) {
    vitaGLUniform1i(vitaGLGetUniformLocation(shaders[1], "ps1_shader"), 0);
}

void cleanup_shaders(void) {
    int i;
    for (i = 0; i < SHADER_COUNT; i++) {
        sceGxmProgramFree((void*)shaders[i]);
    }
}
