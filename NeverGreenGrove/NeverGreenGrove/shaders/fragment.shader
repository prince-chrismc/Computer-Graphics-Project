#version 330 core

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
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 objColor = vec3(texture(textures, textureCoord));

	//folllowing from ta
	//ambient lighting
	float ambientStrength = 0.35f;
	vec3 ambient_contribution = ambientStrength * lightColor;

	//diffuse lighting
	vec3 light_position = vec3(1.0f, 1.0f, 1.0f); //world coords

	vec3 norm = normalize(outNormal);

	vec3 light_direction = normalize(light_position - fragPosition);
	float incident_degree = max(dot(norm, light_direction), 0.0f);
	vec3 diffuse_contribution = incident_degree * lightColor;

	vec3 resultantColour = (ambient_contribution + diffuse_contribution) * objColor;
	color = vec4(resultantColour, 1.0f);
}
