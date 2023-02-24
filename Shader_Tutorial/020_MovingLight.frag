#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

void main(){
    vec2 coords=(gl_FragCoord.xy*2.0-u_resolution)/min(u_resolution.x,u_resolution.y);
    float color=0.0;
    coords.x+=sin(u_time)+cos(u_time*2.1);
    coords.y+=cos(u_time)+sin(u_time*2.1);
    color+=0.1*(abs(sin(u_time))+0.1)/length(coords);
    gl_FragColor=vec4(vec3(color),1.0);
}