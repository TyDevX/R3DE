precision highp float;

uniform sampler2D u_texture0;

varying vec2 v_texcoord0;

void main() {
    vec4 texel = texture2D(u_texture0, v_texcoord0);
    
    // Apply dithering pattern
    vec3 dither_coords = vec3(gl_FragCoord.xy, 0.0);
    vec3 dither_scale = vec3(0.125, 0.125, 0.0);
    vec3 dither_offset = vec3(0.0, 0.5, 0.25);
    vec3 dither_color = vec3(0.0, 0.0, 0.0);
    dither_coords = fract(dither_coords * dither_scale + dither_offset);
    if (texel.r < dither_coords.r) dither_color.r = 1.0;
    if (texel.g < dither_coords.g) dither_color.g = 1.0;
    if (texel.b < dither_coords.b) dither_color.b = 1.0;
    texel.rgb = dither_color;

    gl_FragColor = texel;
}
