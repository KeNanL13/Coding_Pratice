#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

uniform sampler2D u_tex0;
void main(){
    vec2 coords = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);

    vec4 image=texture2D(u_tex0,coords);
    image.r+=sin(coords.x*90.0);
    image.r+=cos(coords.y*90.0);
    gl_FragColor = vec4(image);
}