/*
MIT License

Copyright (c) 2017   Chris McArthur, prince.chrismc(at)gmail(dot)com
                     Daniel P, privorotskyd(at)gmail(dot)com
                     Nicholas G, dj_nick_gattuso(at)hotmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Texture.h"
#include "gl\glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <string>
#include "Shader.h"

Texture::Texture(const char* image_path)
{
   // modified from https://learnopengl.com/#!Getting-started/Textures
   glGenTextures(1, &texture1);
   glBindTexture(GL_TEXTURE_2D, texture1);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   //uncomment this if you want to use gl_clamp_border
   //float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
   //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   int width, height, channel;
   unsigned char* texture_buffer = stbi_load(image_path, &width, &height, &channel, 0);
   if (!texture_buffer)
   {
      std::cout << "Texture loading failed. Try again!" << std::endl;
      std::cout << "Press 'enter' to exit." << std::endl;
      std::getline(std::cin, std::string());
   }
   else
   {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
      glGenerateMipmap(GL_TEXTURE_2D);
   }

   stbi_image_free(texture_buffer);

   glUniform1i(ShaderLinker::GetInstance()->GetUniformLocation("texture1"), 0);
}

Texture::Texture(const char* image_path1, const char* image_path2)
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//uncomment this if you want to use gl_clamp_border
	//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channel;
	unsigned char* texture_buffer = stbi_load(image_path1, &width, &height, &channel, 0);
	if (!texture_buffer)
	{
		std::cout << "Texture loading failed. Try again!" << std::endl;
		std::cout << "Press 'enter' to exit." << std::endl;
		std::getline(std::cin, std::string());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(texture_buffer);

	//-----------for texture 2---------------//
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//uncomment this if you want to use gl_clamp_border
	//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2, channel2;
	unsigned char* texture_buffer2 = stbi_load(image_path2, &width2, &height2, &channel2, 0);
	if (!texture_buffer2)
	{
		std::cout << "Texture loading failed. Try again!" << std::endl;
		std::cout << "Press 'enter' to exit." << std::endl;
		std::getline(std::cin, std::string());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(texture_buffer2);

	
	glUniform1i(ShaderLinker::GetInstance()->GetUniformLocation("texture1"), 0);
	glUniform1i(ShaderLinker::GetInstance()->GetUniformLocation("texture2"), 1);
}

Texture::Texture(const char* image_path1, const char* image_path2, const char* image_path3)
{
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//uncomment this if you want to use gl_clamp_border
	//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, channel;
	unsigned char* texture_buffer = stbi_load(image_path1, &width, &height, &channel, 0);
	if (!texture_buffer)
	{
		std::cout << "Texture loading failed. Try again!" << std::endl;
		std::cout << "Press 'enter' to exit." << std::endl;
		std::getline(std::cin, std::string());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(texture_buffer);

	//-----------for texture 2---------------//
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//uncomment this if you want to use gl_clamp_border
	//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2, channel2;
	unsigned char* texture_buffer2 = stbi_load(image_path2, &width2, &height2, &channel2, 0);
	if (!texture_buffer2)
	{
		std::cout << "Texture loading failed. Try again!" << std::endl;
		std::cout << "Press 'enter' to exit." << std::endl;
		std::getline(std::cin, std::string());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(texture_buffer2);

	//-----------for texture 3---------------//
	glGenTextures(1, &texture3);
	glBindTexture(GL_TEXTURE_2D, texture3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//uncomment this if you want to use gl_clamp_border
	//float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width3, height3, channel3;
	unsigned char* texture_buffer3 = stbi_load(image_path3, &width3, &height3, &channel3, 0);
	if (!texture_buffer2)
	{
		std::cout << "Texture loading failed. Try again!" << std::endl;
		std::cout << "Press 'enter' to exit." << std::endl;
		std::getline(std::cin, std::string());
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width3, height3, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_buffer3);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	stbi_image_free(texture_buffer3);


	glUniform1i(ShaderLinker::GetInstance()->GetUniformLocation("texture1"), 0);
	glUniform1i(ShaderLinker::GetInstance()->GetUniformLocation("texture2"), 1);
	glUniform1i(ShaderLinker::GetInstance()->GetUniformLocation("texture3"), 2);
}