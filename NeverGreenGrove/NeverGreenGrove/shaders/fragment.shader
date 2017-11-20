#version 330 core

in vec4 vertex_color;
in vec2 textureCoord;

out vec4 color;

uniform int object_color;
uniform sampler2D textures;

void main()
{
	//will add a variable to chose when to use the texture eventually
   //color = vertex_color;
	color = texture(textures, textureCoord);
}
