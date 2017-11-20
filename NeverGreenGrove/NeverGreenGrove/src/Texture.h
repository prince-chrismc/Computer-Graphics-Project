#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once

#include "gl\glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include <\Users\Nicholas\Programming\Computer_Graphics_Project\Computer-Graphics-Project\NeverGreenGrove\NeverGreenGrove\src\stb_image.h>

class Texture
{
public:
	Texture() {}
	void createTexture(const char* imagePath);

	unsigned int getTexture();

private:
	unsigned int texture;

	int width;
	int height;
	int channel;
};

#endif