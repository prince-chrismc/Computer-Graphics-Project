//light adjusted from code provided in tutorial

#version 330 core

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;
layout(location = 4) in vec2 textureCoordinate;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec4 vertex_color;
out vec2 textureCoord;
out vec3 pos;
out vec3 fragPosition;

void main()
{
	pos = position;
	fragPosition = vec3(model_matrix * vec4(position, 1.0f));

   gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
   vertex_color = vec4(color, 1.0f);
   textureCoord = vec2(textureCoordinate.x, textureCoordinate.y);
}
