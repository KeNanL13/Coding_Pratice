#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

float circleShape(vec2 position, float radius){
    return step(radius, length(position - vec2(0.5)));
}
void main(){
    vec2 coords=gl_FragCoord.xy/u_resolution;
    vec3 color=vec3(0.0);

    vec2 translate=vec2(0.5*sin(u_time*10.0),0.5*cos(u_time*5.0));
    coords+=translate;
    color+=vec3(circleShape(coords,0.01));
    gl_FragColor=vec4(color,1.0);
}