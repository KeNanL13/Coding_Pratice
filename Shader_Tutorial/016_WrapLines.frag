#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

void main(){
    vec2 coords=gl_FragCoord.xy/u_resolution;
    float color=0.0;
    color+=sin(50.0*coords.x+cos(u_time+coords.y*10.0+sin(coords.x*50.0+u_time*2.0)))*2.0;
    color+=cos(30.0*coords.x+sin(u_time+coords.y*10.0+cos(coords.x*50.0+u_time*2.0)))*2.0;
    color+=sin(20.0*coords.x+cos(u_time+coords.y*10.0+sin(coords.x*50.0+u_time*2.0)))*2.0;
    color+=cos(10.0*coords.x+sin(u_time+coords.y*10.0+cos(coords.x*50.0+u_time*2.0)))*2.0;
    gl_FragColor=vec4(vec3(coords.x+color,coords.y+color,color),1.0);
}