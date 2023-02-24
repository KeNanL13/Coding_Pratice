#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

const int  AMOUNT=40;//个数
const float RADIUS=0.3;//圆半径

void main(){
    vec2 coords=gl_FragCoord.xy/u_resolution;
    vec3 color=vec3(0.0);
    vec2 translate=vec2(-0.5,-0.5);
    coords+=translate;
    // color+=0.1*0.1/length(coords);

    for(int i=0;i<AMOUNT;i++)
    {
        float num=float(AMOUNT);
        float inf=float(i);
        float rad=radians(360.0/num)*inf;
        
        vec2 trans=vec2(sin(rad)*RADIUS,cos(rad)*RADIUS);
        color+=0.1*0.03/(length(coords-trans));
    }

    gl_FragColor=vec4(color,1.0);
}