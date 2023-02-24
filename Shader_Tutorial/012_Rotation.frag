#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

const float PI=3.1415926535;

mat2 rotate(float angle)
{
    return mat2(cos(angle),-sin(angle),sin(angle),cos(angle));
}
float rectShape(vec2 position,vec2 scale){
    scale=vec2(.5)-scale*.5;
    vec2 shaper=vec2(step(scale.x,position.x),step(scale.y,position.y));
    shaper*=vec2(step(scale.x,1.-position.x),step(scale.y,1.-position.y));
    return shaper.x*shaper.y;
}

void main()
{
    vec2 coords=gl_FragCoord.xy/u_resolution;
    vec3 color=vec3(0.0);
    coords-=vec2(0.5);
    coords*=rotate(u_time*PI);
    coords+=vec2(0.5);
    color+=vec3(rectShape(coords,vec2(0.1,0.1)));
    gl_FragColor=vec4(color,1.0);
}