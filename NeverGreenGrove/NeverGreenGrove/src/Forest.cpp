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

#include "Forest.h"
#include "ObjLoader.h"
#include "Shader.h"
#include "Texture.h"
#include <random>                               //std::mt19937
#include <algorithm>
#include <future>

class Forest::TreeA : public Forest::DrawableTree
{
public:
   TreeA() { Scale(glm::vec3(2.5)); }
   void Draw() const;

private:
   class TreeObj
   {
   public:
      ~TreeObj();
      TreeObj(const TreeObj&) = delete;
      TreeObj& operator=(const TreeObj&) = delete;

      static std::shared_ptr<TreeObj> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new TreeObj()); }); return s_Instance; }

      const GLuint GetVAO() const { return m_VAO; }
      const GLsizei GetNumberOfVertices() const { return m_NumVertices; }
      const GLuint GetTexture() const { return m_Texture.getTexture(1); }

   private:
      TreeObj();

      Texture m_Texture;
      GLuint m_VAO;
      GLuint m_Verticies;
      GLuint m_Colors;
      GLuint m_Normals;
      GLuint m_Uvs;

      GLsizei m_NumVertices;

      static std::once_flag s_Flag;
      static std::shared_ptr<TreeObj> s_Instance;
   };
};

class Forest::TreeA2 : public Forest::TreeA
{
public:
   TreeA2() { Scale(glm::vec3(1.0, 1.1, 1.1)); Rotate(90.f); }
};

class Forest::TreeA3 : public Forest::TreeA
{
public:
   TreeA3() { Shear(-0.25f, 0.1f); }
};

class Forest::TreeB : public Forest::DrawableTree
{
public:
   TreeB() { Scale(glm::vec3(2.5)); }
   void Draw() const;

private:
   class TreeObj
   {
   public:
      ~TreeObj();
      TreeObj(const TreeObj&) = delete;
      TreeObj& operator=(const TreeObj&) = delete;

      static std::shared_ptr<TreeObj> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new TreeObj()); }); return s_Instance; }

      const GLuint GetVAO() const { return m_VAO; }
      const GLsizei GetNumberOfVertices() const { return m_NumVertices; }
      const GLuint GetTexture() const { return m_Texture.getTexture(1); }

   private:
      TreeObj();

      Texture m_Texture;
      GLuint m_VAO;
      GLuint m_Verticies;
      GLuint m_Colors;
      GLuint m_Normals;
      GLuint m_Uvs;

      GLsizei m_NumVertices;

      static std::once_flag s_Flag;
      static std::shared_ptr<TreeObj> s_Instance;
   };
};

class Forest::TreeB2 : public Forest::TreeB
{
public:
   TreeB2() { Scale(glm::vec3(1.1, 1.25, 0.9)); Rotate(75.0f); }
};

class Forest::TreeFactory
{
public:
   TreeFactory() = delete;
   static std::shared_ptr<Forest::DrawableTree> GetNewTree();
};

std::once_flag Forest::TreeA::TreeObj::s_Flag;
std::shared_ptr<Forest::TreeA::TreeObj> Forest::TreeA::TreeObj::s_Instance;
std::once_flag Forest::TreeB::TreeObj::s_Flag;
std::shared_ptr<Forest::TreeB::TreeObj> Forest::TreeB::TreeObj::s_Instance;

Forest::TreeA::TreeObj::TreeObj() : m_Texture("assets/treeBark.jpg")
{
   auto shaderProgram = ShaderLinker::GetInstance();
   GLuint PositonIndex = shaderProgram->GetAttributeLocation("position");
   GLuint ColorIndex = shaderProgram->GetAttributeLocation("color");
   GLuint NormalIndex = shaderProgram->GetAttributeLocation("normal");
   GLuint UvIndex = shaderProgram->GetAttributeLocation("textureCoordinate");

   std::vector<glm::vec3> vertices;
   std::vector<glm::vec3> colors;
   std::vector<glm::vec3> normals;
   std::vector<glm::vec2> uvs;
   LoadObjFile("assets/tree_xs.obj", &vertices, &normals, &uvs); //read the vertices from the cube.obj file

   m_NumVertices = (GLsizei)vertices.size();

   for (glm::vec3 vert : vertices)
   {
      (vert.y > 2.10) ? colors.emplace_back(0.075, 0.545, 0.271) : colors.emplace_back(0.545, 0.271, 0.075);
   }

   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_Verticies);
   glGenBuffers(1, &m_Colors);
   glGenBuffers(1, &m_Normals);
   glGenBuffers(1, &m_Uvs);

   // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_Verticies);
   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(PositonIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(PositonIndex);

   glBindBuffer(GL_ARRAY_BUFFER, m_Colors);
   glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(ColorIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(ColorIndex);

   glBindBuffer(GL_ARRAY_BUFFER, m_Normals);
   glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(NormalIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(NormalIndex);

   glBindBuffer(GL_ARRAY_BUFFER, m_Uvs);
   glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(UvIndex, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(UvIndex);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindVertexArray(0);
}

Forest::TreeA::TreeObj::~TreeObj()
{
   glDeleteBuffers(1, &m_Verticies);
   glDeleteBuffers(1, &m_Colors);
   glDeleteBuffers(1, &m_Normals);
   glDeleteBuffers(1, &m_Uvs);
   glDeleteVertexArrays(1, &m_VAO);
}

Forest::TreeB::TreeObj::TreeObj() : m_Texture("assets/wall.jpg")
{
   auto shaderProgram = ShaderLinker::GetInstance();
   GLuint PositonIndex = shaderProgram->GetAttributeLocation("position");
   GLuint ColorIndex = shaderProgram->GetAttributeLocation("color");
   GLuint NormalIndex = shaderProgram->GetAttributeLocation("normal");
   GLuint UvIndex = shaderProgram->GetAttributeLocation("textureCoordinate");

   std::vector<glm::vec3> vertices;
   std::vector<glm::vec3> colors;
   std::vector<glm::vec3> normals;
   std::vector<glm::vec2> uvs;
   LoadObjFile("assets/tree2_xs.obj", &vertices, &normals, &uvs); //read the vertices from the cube.obj file

   m_NumVertices = (GLsizei)vertices.size();

   for (glm::vec3 vert : vertices)
   {
      (vert.y > 2.00) ? colors.emplace_back(0.075, 0.545, 0.271) : colors.emplace_back(0.545, 0.271, 0.075);
   }

   glGenVertexArrays(1, &m_VAO);
   glGenBuffers(1, &m_Verticies);
   glGenBuffers(1, &m_Colors);
   glGenBuffers(1, &m_Normals);
   glGenBuffers(1, &m_Uvs);

   // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   glBindVertexArray(m_VAO);

   glBindBuffer(GL_ARRAY_BUFFER, m_Verticies);
   glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(PositonIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(PositonIndex);

   glBindBuffer(GL_ARRAY_BUFFER, m_Colors);
   glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), &colors.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(ColorIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(ColorIndex);

   glBindBuffer(GL_ARRAY_BUFFER, m_Normals);
   glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(NormalIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(NormalIndex);

   glBindBuffer(GL_ARRAY_BUFFER, m_Uvs);
   glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(UvIndex, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(UvIndex);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindVertexArray(0);
}

Forest::TreeB::TreeObj::~TreeObj()
{
   glDeleteBuffers(1, &m_Verticies);
   glDeleteBuffers(1, &m_Colors);
   glDeleteBuffers(1, &m_Normals);
   glDeleteBuffers(1, &m_Uvs);
   glDeleteVertexArrays(1, &m_VAO);
}

void Forest::TreeA::Draw() const
{
   auto shaderProgram = ShaderLinker::GetInstance();
   glm::mat4 myModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
   shaderProgram->SetUniformMat4("model_matrix", myModelMatrix);
   shaderProgram->SetUniformInt("object_type", 0);

   glBindVertexArray(TreeObj::GetInstance()->GetVAO());
   glBindTexture(GL_TEXTURE_2D, TreeObj::GetInstance()->GetTexture());
   glDrawArrays(GL_TRIANGLES, 0, TreeObj::GetInstance()->GetNumberOfVertices());
   glBindTexture(GL_TEXTURE_2D, 0);
   glBindVertexArray(0);
}

void Forest::TreeB::Draw() const
{
   auto shaderProgram = ShaderLinker::GetInstance();
   glm::mat4 myModelMatrix = m_TranslationMatrix * m_RotationMatrix * m_ScaleMatrix;
   shaderProgram->SetUniformMat4("model_matrix", myModelMatrix);
   shaderProgram->SetUniformInt("object_type", 0);

   glBindVertexArray(TreeObj::GetInstance()->GetVAO());
   glBindTexture(GL_TEXTURE_2D, TreeObj::GetInstance()->GetTexture());
   glDrawArrays(GL_TRIANGLES, 0, TreeObj::GetInstance()->GetNumberOfVertices());
   glBindTexture(GL_TEXTURE_2D, 0);
   glBindVertexArray(0);
}

std::shared_ptr<Forest::DrawableTree> Forest::TreeFactory::GetNewTree()
{
   std::random_device rd;
   std::mt19937 g(rd());

   switch (g() % 5 + 1)
   {
   case 1:
      return std::make_shared<Forest::TreeA>();
   case 2:
      return std::make_shared<TreeA2>();
   case 3:
     return std::make_shared<Forest::TreeA3>();
   case 4:
      return std::make_shared<Forest::TreeB>();
   case 5:
      return std::make_shared<Forest::TreeB2>();
   default:
      return std::make_shared<Forest::TreeA>();
   }
}

Forest::Forest(const std::vector<std::vector<glm::vec3>>& grid_2d)
{
   auto future_forest = std::async(std::launch::async, [] {
       std::vector<std::shared_ptr<DrawableTree>> retval(256);
       std::generate(retval.begin(), retval.end(), TreeFactory::GetNewTree);
       return retval;
   });
   //std::async(std::launch::async, [this] {
   //   std::generate(m_ObjectSpace.begin(), m_ObjectSpace.end(), [] { return true; });
   //});
   std::generate(m_HeightMap.begin(), m_HeightMap.end(), [grid_2d] {
      static size_t x = 0, y = 0;
      if(x == 128) x = 0;
      float retval = grid_2d.at(x).at(y).y;
      if (++y == 128) { x++; y = 0; }
      return retval;
   });

   static std::random_device rd;
   static std::mt19937 g(rd());

   auto GenCoord = [] {
      return 1 + (g() % 126);
   };
   auto GetDegree = [] {
      return float(g() % 360);
   };

   auto tree_vec = future_forest.get();

   while (!tree_vec.empty())
   {
      size_t x = GenCoord();
      size_t y = GenCoord();

      float min_point = std::min({m_HeightMap[{ x - 1, y - 1  }], m_HeightMap[{ x - 1 , y }], m_HeightMap[{ x - 1, y + 1 }],
                                 m_HeightMap[{ x, y - 1  }], m_HeightMap[{ x, y }], m_HeightMap[{ x, y + 1 }],
                                 m_HeightMap[{ x + 1, y - 1  }], m_HeightMap[{ x + 1, y }], m_HeightMap[{ x + 1, y + 1 }]});

      auto tree = tree_vec.back();
      tree->Translate(glm::vec3(x, min_point - 0.05, y));
      tree->Rotate(GetDegree());
      m_Map.emplace(Point{ x, y }, tree);
      tree_vec.pop_back();
   }
}
