#include "Light.h"
#include "Shader.h"

Light::Light()
{
	//set the initial position 
	position = { 100.0f,0.0f, 100.0f };
}

void Light::newPosition()
{
	//calculate new position using time
}

void Light::Draw()
{
	GLuint PositonIndex = ShaderLinker::GetInstance()->GetAttributeLocation("position");
}

