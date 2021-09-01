#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 proj;
uniform mat4 model;



void main()
{
/*mat4 x = mat4(0.88, -0.48, 0.0, 0.0,*/
                /*0.48, 0.88, 0.0, 0.0,*/
                /*0.0, 1.0, 1.0, 0.0,*/
                /*0.0, 0.0, 0.0, 1.0);*/
    gl_Position = (vec4(aPos, 1.0f) * model) * proj; 
}
