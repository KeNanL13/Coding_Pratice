#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;

float circleShape(vec2 position,float radius)
{
    return step(radius,length(position-vec2(0.5,0.5)));
}
void main()
{
    vec2 coords=gl_FragCoord.xy/u_resolution;
    vec3 color=vec3(0.0);
    coords+=vec2(0.4*sin(u_time),0.4*sin(u_time)*cos(u_time));
    color=vec3(circleShape(coords,0.1));
    gl_FragColor=vec4(color,1.0);

}