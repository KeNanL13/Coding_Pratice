#ifdef GL_ES
precision mediump float;
#endif
uniform vec2 u_resolution;
uniform float u_time;

uniform sampler2D u_tex0;

void main(){
   vec2 coords=gl_FragCoord.xy/u_resolution;
   vec3 color=vec3(0.0);
   coords.x+=sin(u_time);
   gl_FragColor=texture2D(u_tex0,coords);   
}