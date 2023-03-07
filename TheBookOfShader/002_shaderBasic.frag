#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

#define PI 3.14159265359

float line (vec2 coords)
{
    return smoothstep(0.02,0.0 ,abs(step(0.5,coords.x)-coords.y) );
    
}
float plot(vec2 st,float pct)
{
    return smoothstep(pct-0.02,pct ,st.y )-smoothstep(pct,pct+0.02 ,st.y );
}

float testSmoothStep(vec2 st)
{
    return smoothstep(0.5,0.0 ,st.x );
}
void main(){
    vec2 coord = gl_FragCoord.xy/u_resolution;
    
    float y=pow(coord.x,5.0);
    y=step(0.5,coord.x);
    y=smoothstep(0.1,0.9,coord.x );
    y = smoothstep(0.2,0.5,coord.x) - smoothstep(0.5,0.8,coord.x);
    y=ceil(sin(PI*coord.x+u_time));
    y=mod(coord.x,0.5);
    y=fract(coord.x);
    y=ceil(coord.x);
    y=sign(sin(coord.x+u_time));
    y=clamp(coord.x,0.0 ,1.0 );
    y=min(0.5,coord.x);
    vec3 color = vec3(y);

    float pct=plot(coord,y);
    color=(1.0-pct)*color+pct*vec3(0.0,1.0,0.0);
    
    // color=vec3(testSmoothStep(coord));
    // color=vec3(line(coord));
    gl_FragColor = vec4( color,1.0);
}