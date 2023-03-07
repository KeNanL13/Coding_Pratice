#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

const float PI =3.14159265359;
vec3 colorA=vec3(0.149,0.141,0.912);
vec3 colorB=vec3(1.0,0.833,0.224);

float plot(vec2 st,float pct)
{
    return smoothstep(pct-0.01,pct ,st.y )-smoothstep(pct,pct+0.01 ,st.y );
}

vec3 rgb2hsb( in vec3 c ){
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz),
                 vec4(c.gb, K.xy),
                 step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r),
                 vec4(c.r, p.yzx),
                 step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)),
                d / (q.x + e),
                q.x);
}
vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}

void main(){
    vec2 coord = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);
    vec3 pct=vec3(coord.x);

    // pct.r=smoothstep(0.0,1.0 ,coord.x );
    // pct.g=sin(coord.x*3.14);
    // pct.b=pow(coord.x,0.5);
    
    color=mix(colorA,colorB,pct);

    color=mix(color,vec3(1.0,0.0,0.0),plot(coord,pct.r));
    color=mix(color,vec3(0.0,1.0,0.0),plot(coord,pct.g));
    color=mix(color,vec3(0.0,0.0,1.0),plot(coord,pct.b));

    color=hsb2rgb(vec3(coord.x,1.0,coord.y));

    //Use polar coordinates instead of cartesian
    vec2 toCenter=vec2(0.5)-coord;
    float angle = atan(toCenter.y,toCenter.x);
    float radius=length(toCenter)*2.0;

    color=hsb2rgb(vec3((angle/(2.0*PI)*1.0)+0.5,radius,1.0));


    gl_FragColor = vec4(color, 1.0);
}