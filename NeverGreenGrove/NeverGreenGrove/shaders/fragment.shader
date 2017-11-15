#version 330 core

in vec4 vertex_color;
out vec4 color;
uniform int object_color;

void main()
{
   color = vertex_color;
}
