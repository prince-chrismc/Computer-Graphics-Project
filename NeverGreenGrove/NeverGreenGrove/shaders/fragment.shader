#version 330 core

//uniform sampler2D gSamplers[2];
//uniform int numTextures;

in vec4 vertex_color;
in vec2 textureCoord;
uniform int object;
in vec3 fragPosition;

out vec4 color;

uniform int object_color;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	//will add a variable to chose when to use the texture eventually
   //color = vertex_color;
	
	if (object == 1) {
		color = texture(texture1, textureCoord);
	}
	else { color = texture(texture2, textureCoord); }
}
