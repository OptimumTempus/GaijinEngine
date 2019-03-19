#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>


uniform mat4 projection;

void main()
{

    gl_Position =  vertex;
}  