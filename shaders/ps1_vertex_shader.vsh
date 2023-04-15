uniform mat4 u_mvp;
uniform mat4 u_model;
uniform vec3 u_camera_pos;
uniform vec2 u_camera_rot;

attribute vec4 a_position;
attribute vec2 a_texcoord0;

varying vec2 v_texcoord0;

void main() {
    // Transform vertex position by model matrix
    vec4 world_pos = u_model * a_position;
    
    // Transform vertex position by view matrix (camera position and rotation)
    vec3 camera_pos = vec3(u_camera_pos.x, u_camera_pos.y, u_camera_pos.z);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 forward = vec3(0.0, 0.0, -1.0);
    mat4 view = mat4(1.0);
    view = rotate(view, u_camera_rot.x, up);
    view = rotate(view, u_camera_rot.y, vec3(1.0, 0.0, 0.0));
    view = translate(view, -camera_pos);
    vec4 view_pos = view * vec4(world_pos.xyz, 1.0);
    
    // Transform vertex position by projection matrix
    vec4 projected_pos = u_mvp * view_pos;
    
    // Transform texture coordinates
    v_texcoord0 = a_texcoord0;

    gl_Position = projected_pos;
}
