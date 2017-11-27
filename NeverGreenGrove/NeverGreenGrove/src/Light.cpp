#include "Light.h"
#include "Shader.h"

Light::Light()
{
	//set the initial position 
	position = { 100.0f,100.0f, 100.0f };
}

void Light::newPosition(float time)
{
	position = { 100.0f + (time * 100), 100.0f + (time*100), 100.0f + (time * 100) };
}

void Light::Draw(float time)
{
	newPosition(time);
	ShaderLinker::GetInstance()->SetUniformVec3("light_position", position);
}

