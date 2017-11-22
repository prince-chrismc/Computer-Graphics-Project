/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

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

#include "DrawableObject.h"
#include "Shader.h"

DrawableObject::DrawableObject(const std::vector<glm::vec3> verticies, const std::vector<glm::vec3> colors, const std::vector<GLuint> indicies)
{
   auto shaderProgram = ShaderLinker::GetInstance();
   GLuint PositonIndex = shaderProgram->GetAttributeLocation("position");
   GLuint ColorIndex = shaderProgram->GetAttributeLocation("color");

   glGenVertexArrays(1, &m_VAO);
   glBindVertexArray(m_VAO);

   glGenBuffers(1, &m_Verticies);
   glBindBuffer(GL_ARRAY_BUFFER, m_Verticies);
   glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(glm::vec3), &verticies.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(PositonIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(PositonIndex);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenBuffers(1, &m_Colors);
   glBindBuffer(GL_ARRAY_BUFFER, m_Colors);
   glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(ColorIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(ColorIndex);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenBuffers(1, &m_Indicies);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), &indicies.front(), GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glBindVertexArray(0);

   m_NumVertices = (GLsizei)verticies.size();
   m_NumIndicies = (GLsizei)indicies.size();
}

//------------for textures------------------
DrawableObject::DrawableObject(const std::vector<glm::vec3> verticies, const char *texturePath, const std::vector<GLuint> indicies)
{
	Texture temp("assets/wall.jpg");
	m_Texture = temp;

	auto shaderProgram = ShaderLinker::GetInstance();
	GLuint PositonIndex = shaderProgram->GetAttributeLocation("position");
	GLuint textureIndex = shaderProgram->GetAttributeLocation("textureCoordinate");

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_Verticies);
	glGenBuffers(1, &m_Indicies);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_Verticies);
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(glm::vec3), &verticies.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), &indicies.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(PositonIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(PositonIndex);

	glVertexAttribPointer(textureIndex, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(textureIndex);
	glBindTexture(GL_TEXTURE_2D, m_Texture.getTexture());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	m_NumVertices = (GLsizei)verticies.size();
	m_NumIndicies = (GLsizei)indicies.size();
}

void DrawableObject::Delete()
{
   glDeleteBuffers(1, &m_Verticies);
   glDeleteBuffers(1, &m_Colors);
   glDeleteBuffers(1, &m_Indicies);
   glDeleteVertexArrays(1 ,&m_VAO);
}

void DrawableObject::Draw(const RenderMode& render_mode) const
{
   switch (render_mode)
   {
   case RenderMode::POINTS:
      glBindVertexArray(m_VAO);
      glDrawArrays(GL_POINTS, 0, m_NumVertices);
      glBindVertexArray(0);
      break;

   case RenderMode::TRIANGLES:
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
      glDrawElements(GL_TRIANGLES, m_NumIndicies, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      break;

   case RenderMode::LINES:
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
      glDrawElements(GL_LINES, m_NumIndicies, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      break;
   }
}

unsigned int DrawableObject::getTexture() { return m_Texture.getTexture(); }
