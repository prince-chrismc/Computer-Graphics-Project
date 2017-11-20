#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include "gl\glew.h"

class Texture
{
public:
	Texture() {}
	void createTexture(const char* imagePath);
	float getCoordinates();
	unsigned int getTexture();

private:
	unsigned int texture;

	int width;
	int height;
	int channel;

	float textureCoord[] = {// texture coords
		1.0f, 1.0f,   // top right
		1.0f, 0.0f,   // bottom right
		0.0f, 0.0f,   // bottom left
		0.0f, 1.0f    // top left 
	}
};

#endif