#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

void main(){
   vec2 coords=gl_FragCoord.xy*1.0-u_resolution;
   vec3 color=vec3(0.0);
   color+=abs(cos(coords.x/20.0)+sin(coords.y/20.0)-cos(u_time));
   gl_FragColor=vec4(color,1.0);   
}