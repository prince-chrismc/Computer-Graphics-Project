#pragma once

#include "glm\matrix.hpp"

class Light
{
public:
	Light() {}

	void Draw();

private:
	glm::vec3 position;

	void newPosition();
};
