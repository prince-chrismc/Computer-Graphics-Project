#version 330 core

out vec4 color;
uniform int object_color;

void main()
{
   color = (object_color == 0) ? vec4(1.0f, 0.0f, 0.0f, 1.0f) : // red
           (object_color == 1) ? vec4(0.0f, 1.0f, 0.0f, 1.0f) : // green
           (object_color == 2) ? vec4(0.0f, 0.0f, 1.0f, 1.0f) : // blue
           (object_color == 3) ? vec4(0.5f, 0.5f, 0.5f, 1.0f) : // grey
           (object_color == 4) ? vec4(1.0f, 0.9333f, 0.0f, 1.0f) : // pacman yellow
           (object_color == 5) ? vec4(0.0f, 0.5f, 0.5f, 1.0f) : // teal
           vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
