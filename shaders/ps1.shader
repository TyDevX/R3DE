varying vec4 v_color;
varying vec2 v_texcoord;

uniform sampler2D u_texture;
uniform mat4 u_mvp_matrix;

void main() {
    vec4 texel = texture2D(u_texture, v_texcoord);
    float brightness = dot(texel.rgb, vec3(0.299, 0.587, 0.114));
    texel.rgb = vec3(brightness);
    gl_FragColor = texel * v_color;
    gl_Position = u_mvp_matrix * gl_Vertex;
}
