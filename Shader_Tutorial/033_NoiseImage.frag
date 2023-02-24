#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

uniform sampler2D u_tex0;

float random2d(vec2 coord){
    return fract(sin(dot(coord.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

void main(){
    vec2 coords = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);
    vec4 image=texture2D(u_tex0,coords);
    float noise=(random2d(coords));
    image.r+=noise+u_time;
    image.g+=noise;
    image.b+=noise;
    gl_FragColor = image;
}