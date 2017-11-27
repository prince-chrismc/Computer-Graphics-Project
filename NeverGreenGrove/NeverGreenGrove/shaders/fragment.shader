#version 330 core

in vec3 vertex_color;
in vec2 textureCoord;
in vec3 outNormal;
in vec3 fragPosition;

out vec4 color;

uniform int object_type;
uniform int object_color;
uniform sampler2D textures;

void main()
{
   vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

   vec3 objColor = vec3(texture(textures, textureCoord));
   if (object_type == 1){ objColor = vertex_color; }

   //folllowing from ta
   //ambient lighting
   float ambientStrength = 0.85f;
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
