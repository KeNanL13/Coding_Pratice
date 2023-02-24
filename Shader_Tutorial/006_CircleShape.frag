#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;

float circleShape(vec2 position,float radius)
{
    float len=length(position-vec2(0.5));
    if(radius<len)
    {
        return 1.0;
    }
    else{
        return len;
    }
    // return step(radius,length(position-vec2(0.5)));
}
void main(){
    vec2 position=gl_FragCoord.xy/u_resolution;
    
    vec3 color=vec3(0.0);
    float circle=circleShape(position,0.5);
    color=vec3(circle);
    gl_FragColor=vec4(1,1,circle,1.0);
}