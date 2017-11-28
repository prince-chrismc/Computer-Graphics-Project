//fog referenced: http://in2gpu.com/2014/07/22/create-fog-shader/

#version 330 core

in vec3 vertex_color;
in vec2 textureCoord;
in vec3 outNormal;
in vec3 fragPosition;
in vec4 eyeSpace;

out vec4 color;

uniform int object_type;
uniform int object_color;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   vec3 lightColor = vec3(0.7f, 0.7f, 0.7f);

   vec3 objColor = vec3(texture(texture2, textureCoord));
   if (object_type == 1){ objColor = vertex_color; }

   float fogCoordinate = abs(eyeSpace.z / eyeSpace.w); //ranged based
   //float fogCoordinate = abs(eyeSpace.z); //plane based
   vec4 fogColour = vec4(0.05f, 0.075f, 0.075f, 1.0f);
   float startFog = 0.0f;
   float endFog = 250.0f;

   float fogIntensity = 1.0 - clamp((endFog - fogCoordinate) / (endFog - startFog), 0.0, 1.0);

   //folllowing from ta
   //ambient lighting
   float ambientStrength = 0.75f;
   vec3 ambient_contribution = ambientStrength * lightColor;

   //diffuse lighting
   vec3 light_position = vec3(1.0f, 1.0f, 1.0f); //world coords

   vec3 norm = normalize(outNormal);

   vec3 light_direction = normalize(light_position - fragPosition);
   float incident_degree = max(dot(norm, light_direction), 0.0f);
   vec3 diffuse_contribution = incident_degree * lightColor;

   vec3 resultantColour = (ambient_contribution + diffuse_contribution) * objColor;
   color = vec4(resultantColour, 1.0f);

   color = mix(color, fogColour, fogIntensity);
}
