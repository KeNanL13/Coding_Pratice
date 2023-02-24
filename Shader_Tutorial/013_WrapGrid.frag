#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

void main(){
    vec2 coords=gl_FragCoord.xy/u_resolution;
    vec3 color=vec3(0);
    // color+=sin(coords.x*cos(u_time/60.0)*60.0+sin(coords.y*sin(u_time/6.0)*10.0));//波浪
    color+=sin(coords.x*cos(u_time/60.0)*60.0)+sin(coords.y*cos(u_time/15.0)*10.0);
    color+=cos(coords.x*sin(u_time/60.0)*60.0)+cos(coords.y*sin(u_time/15.0)*10.0);
    // color*=sin(u_time/15.0)*0.5;
    // color+=sin(coords.x*60.0+coords.y*60.0);
    gl_FragColor=vec4(color,1.0);   
}