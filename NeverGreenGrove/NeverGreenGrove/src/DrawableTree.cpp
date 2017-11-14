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

#include "DrawableTree.h"
#include "ObjLoader.h"
#include "Shader.h"

std::once_flag TreeObj::s_Flag;
std::shared_ptr<TreeObj> TreeObj::s_Instance;

TreeObj::TreeObj()
{
   auto shaderProgram = ShaderLinker::GetInstance();
   GLuint PositonIndex = shaderProgram->GetAttributeLocation("position");
   GLuint ColorIndex = shaderProgram->GetAttributeLocation("color");
   GLuint NormalIndex = shaderProgram->GetAttributeLocation("normal");
   GLuint UvIndex = shaderProgram->GetAttributeLocation("color");

   std::vector<glm::vec3> vertices;
   std::vector<glm::vec3> normals;
   std::vector<glm::vec2> uvs;
   LoadObjFile("assets/Tree2.obj", &vertices, &normals, &uvs); //read the vertices from the cube.obj file

   GLuint VAO_cube;
   glGenVertexArrays(1, &VAO_cube);
   GLuint vertices_VBO, normals_VBO, uv_VBO;
   glGenBuffers(1, &vertices_VBO);
   glGenBuffers(1, &normals_VBO);
   glGenBuffers(1, &uv_VBO);

   // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   glBindVertexArray(VAO_cube);

   glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(PositonIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(PositonIndex);

   glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
   glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(NormalIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(NormalIndex);

   glBindBuffer(GL_ARRAY_BUFFER, uv_VBO);
   glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec3), &uvs.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(UvIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(UvIndex);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindVertexArray(0);
}

TreeObj::~TreeObj()
{
   glDeleteBuffers(1, &m_Verticies);
   glDeleteBuffers(1, &m_Colors);
   glDeleteBuffers(1, &m_Normals);
   glDeleteBuffers(1, &m_Uvs);
   glDeleteVertexArrays(1, &m_VAO);
}

void DrawableTree::Draw()
{
   glBindVertexArray(TreeObj::GetInstance()->GetVAO());
   glDrawArrays(GL_TRIANGLES, 0, TreeObj::GetInstance()->GetNumberOfVertices());
   glBindVertexArray(0);
}
