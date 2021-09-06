#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNorm;

uniform mat4 proj;
uniform mat4 model;

uniform vec4 u_color;
uniform float u_ambient;

out vec3 norm;
out vec3 f_pos;

out vec3 ambient;

void main()
{
    norm = (vec4(aNorm, 0.0f) * model).xyz;
    norm = normalize(norm); 
    vec4 aPos_m = vec4(aPos, 1.0f) * model;
    f_pos = (aPos_m).xyz;

    ambient = (u_ambient * u_color).xyz;

    gl_Position = vec4(aPos, 1.0f) * model * proj; 

}
