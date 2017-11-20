#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

void Texture::createTexture(const char* imagePath)
{
	//modified from learnopengl.com
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	unsigned char *dataTemp = stbi_load(imagePath, &width, &height, &channel, 0);
	if (!dataTemp)
	{
		std::cout << "Texture loading failed. Try again!" << std::endl;
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataTemp);
		glGenerateMipmap(GL_TEXTURE_2D);
	
	}

	stbi_image_free(dataTemp);
}

unsigned int Texture::getTexture() { return texture; }

float Texture::getCoordinates() { return textureCoord[1]; }