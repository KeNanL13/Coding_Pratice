#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

const int AMOUNT=12;

void main(){
    vec2 coords=20.0*(gl_FragCoord.xy-u_resolution/2.0)/min(u_resolution.y,u_resolution.x);
    
    float len;

    for(int i=0;i<AMOUNT;i++)
    {
        len=length(vec2(coords.x,coords.y));

        coords.x=coords.x-cos(coords.y+sin(len))+cos(u_time/9.0);
        coords.y=coords.y+sin(coords.x+cos(len))+sin(u_time/12.0);
    }
    gl_FragColor=vec4(cos(len*2.0),cos(len*3.0),cos(len*1.0),1.0 );
}