#pragma once

#include "glm\matrix.hpp"

class Light
{
public:
	Light();

	void Draw(float time);

private:
	glm::vec3 position;

	void newPosition(float time);
};
