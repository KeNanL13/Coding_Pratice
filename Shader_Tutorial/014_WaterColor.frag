#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

void main(){
    vec2 coords=6.0*gl_FragCoord.xy/u_resolution;
    
    for(int n=1;n<8;n++)
    {
        float i=float(n);
        coords+=vec2(0.7/i*sin(i*coords.y+u_time+0.3*i)+0.8,0.4/i*sin(coords.x+u_time+0.3*i)+1.6);
    }
    // coords+-*/=(vec2(0.7/sin(coords.y+u_time+0.3)+0.8,0.4/sin(coords.x+u_time+0.3)+1.6));
    vec3 color=vec3(0.5*sin(coords.x)+0.5,0.5*sin(coords.y)+0.5,sin(coords.x+coords.y));
    
    gl_FragColor=vec4(color,1.0);
}