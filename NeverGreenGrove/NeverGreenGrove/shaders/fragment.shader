#version 330 core

uniform sampler2D gSamplers[2];
uniform int numTextures;

in vec4 vertex_color;
in vec2 textureCoord;
in vec3 outNormal;
in vec3 fragPosition;

out vec4 color;

uniform int object_color;
uniform sampler2D textures;

void main()
{
	//will add a variable to chose when to use the texture eventually
   //color = vertex_color;
	for (int i = 0; i < numTextures; i++)
	{
		if (i == 0)
		{
			color = texture2D(gSamplers[0], textureCoord);
		}
		else
		{
			color = texture2D(gSamplers[1], textureCoord);
		}
	}

		//color = texture(textures, textureCoord);
}
