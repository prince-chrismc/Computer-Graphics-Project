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

#include "TerrainBlock.h"
#include "Shader.h"
#include "glm\common.hpp"                       // clamp
#include <random>                               // mt19937
#include <algorithm>                            // std::random_shuffle
#include <cmath>

constexpr float PI = 3.14159265358979323846f;

TerrainBlock::DrawableTerrain::DrawableTerrain(const std::vector<glm::vec3> verticies, const std::vector<glm::vec3> colors, const std::vector<glm::vec3> normals, const std::vector<GLuint> indicies, const std::vector<glm::vec2> uvs) : m_Texture("assets/grass.jpg")
{
   auto shaderProgram = ShaderLinker::GetInstance();
   GLuint PositonIndex = shaderProgram->GetAttributeLocation("position");
   GLuint ColorIndex = shaderProgram->GetAttributeLocation("color");
   GLuint NormalIndex = shaderProgram->GetAttributeLocation("normal");
   GLuint UVIndex = shaderProgram->GetAttributeLocation("textureCoordinate");

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

   glGenBuffers(1, &m_Normals);
   glBindBuffer(GL_ARRAY_BUFFER, m_Normals);
   glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(NormalIndex, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(NormalIndex);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenBuffers(1, &m_UVs);
   glBindBuffer(GL_ARRAY_BUFFER, m_UVs);
   glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(UVIndex, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(UVIndex);
   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenBuffers(1, &m_Indicies);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(GLuint), &indicies.front(), GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

   glBindVertexArray(0);

   m_NumVertices = (GLsizei)verticies.size();
   m_NumIndicies = (GLsizei)indicies.size();
}

TerrainBlock::DrawableTerrain::~DrawableTerrain()
{
   glDeleteBuffers(1, &m_Verticies);
   glDeleteBuffers(1, &m_Colors);
   glDeleteBuffers(1, &m_Normals);
   glDeleteBuffers(1, &m_Indicies);
   glDeleteBuffers(1, &m_UVs);
   glDeleteVertexArrays(1, &m_VAO);
}

void TerrainBlock::DrawableTerrain::Draw(const RenderMode& render_mode) const
{
   ShaderLinker::GetInstance()->SetUniformInt("object_type", 0);

   switch (render_mode)
   {
   case RenderMode::LINES:
      glBindVertexArray(m_VAO);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
      glDrawElements(GL_LINES, m_NumIndicies, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
      break;

   case RenderMode::TRIANGLES:
	   glBindVertexArray(m_VAO);
	   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
	   glDrawElements(GL_TRIANGLES, m_NumIndicies, GL_UNSIGNED_INT, 0);
	   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	   glBindVertexArray(0);
	   break;

   case RenderMode::TRIANGLE_STRIPS:
      glBindVertexArray(m_VAO);
	  glBindTexture(GL_TEXTURE_2D, GetTexture());
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Indicies);
      glDrawElements(GL_TRIANGLE_STRIP, m_NumIndicies, GL_UNSIGNED_INT, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	  glBindTexture(GL_TEXTURE_2D, 0);
	  glBindVertexArray(0);
      break;

   default: break;
   }
}

// ------------------------------------------------------------------------------------------------ //
//                                       BUILDER FUNCTIONS                                          //
// ------------------------------------------------------------------------------------------------ //

void TerrainBlock::Builder::BuildFlatTerrain() // create a simple flat terrain
{
   GLuint counter = 0;
   std::vector<std::vector<GLuint>> indices_2d;

   for (int i = 0; i < CHUNK_LENGTH; i++)
   {
      std::vector<glm::vec3> temp_builder;
      std::vector<glm::vec3> temp_color;
      std::vector<glm::vec3> temp_normals;
      std::vector<GLuint> temp_indices;
      for (int j = 0; j < CHUNK_LENGTH; j++)
      {
         temp_builder.emplace_back(i, 0, j);
         temp_indices.emplace_back(counter++);
         UVs.emplace_back(glm::vec2(i, j));
         temp_normals.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f)); // directly up
         temp_color.emplace_back(glm::vec3(0.4f, 0.2f, 0.04f)); // brownish color
      }
      normals_2d.emplace_back(temp_normals);
      grid_2d.emplace_back(temp_builder);
      color_2d.emplace_back(temp_color);
      indices_2d.emplace_back(temp_indices);
   }

   indices = createEBO(indices_2d);
}

void TerrainBlock::Builder::GenerateVertices()
{
   // Remember: points are (x,y,z) with
   // x = width
   // y = height
   // z = depth

   // create a simple flat terrain to start
   BuildFlatTerrain();

   constexpr int MIN_RADIUS = TerrainBlock::CHUNK_LENGTH / 8;
   constexpr int MAX_RADIUS = TerrainBlock::CHUNK_LENGTH / 4;
   constexpr int INNER_LENGTH = TerrainBlock::CHUNK_LENGTH - 2 * MIN_RADIUS;

   constexpr float MIN_HEIGHT = MIN_RADIUS / 2.0f;
   constexpr float MAX_HEIGHT = 48.0f;

   // random shuffle
   std::random_device rd;
   std::mt19937 gen(rd());

   // max hills
   const int hill_qty = 3 + gen() % 7;

   // creates indicies for hill peaks
   std::vector<int> horizontal_peaks;
   std::vector<int> depth_peaks;
   for (int i = 0; i < hill_qty; i++)
   {
      horizontal_peaks.emplace_back(INNER_LENGTH / hill_qty + (INNER_LENGTH / hill_qty)*i);
      depth_peaks.emplace_back(INNER_LENGTH / hill_qty + (INNER_LENGTH / hill_qty)*i);
   }

   // shuffle the indicies
   std::shuffle(horizontal_peaks.begin(), horizontal_peaks.end(), gen);
   std::shuffle(depth_peaks.begin(), depth_peaks.end(), gen);

   // create all the hills --------------------------------------------------------------------------------------------------------------------------
   std::vector<Hill> hills;

   // Saturate their info, create peaks
   for (int i = 0; i < hill_qty; i++)
   {
      const int max_r = (int)std::min({ (float)horizontal_peaks.at(i), (float)depth_peaks.at(i), (float)CHUNK_LENGTH - horizontal_peaks.at(i), (float)CHUNK_LENGTH - depth_peaks.at(i), (float)MAX_RADIUS });
      const float temp_radius = float(max_r <= MIN_RADIUS) ? float(max_r) : float(MIN_RADIUS + (gen() % (max_r - MIN_RADIUS)));
      const float temp_height = (MIN_HEIGHT + gen() % (int)(temp_radius - MIN_HEIGHT));

      grid_2d.at(horizontal_peaks.at(i)).at(depth_peaks.at(i)).y = temp_height;
      Hill new_hill(temp_height, temp_radius, (float)horizontal_peaks.at(i), (float)depth_peaks.at(i));
      hills.emplace_back(new_hill);
      color_2d.at((size_t)new_hill.x).at((size_t)new_hill.z) = glm::vec3(0.4f + 0.6*(temp_height / MAX_HEIGHT), 0.2f + 0.8*(temp_height / MAX_HEIGHT), 0.04f + 0.96*(temp_height / MAX_HEIGHT));
   }

   // Change all points inside their radius
   // to find wether a point is in a circle, use https://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
   for (int i = 0; i < TerrainBlock::CHUNK_LENGTH; i++)
   {
      for (int j = 0; j < TerrainBlock::CHUNK_LENGTH; j++)
      {
         //check every hills
         for (const auto hill : hills)
         {
            //check if in mountain
            const float distance = std::sqrt((i - hill.x)*(i - hill.x) + (j - hill.z)*(j - hill.z));
            if (distance <= hill.radius)
            {
               //Using a simple cosine function A*cos(nx) + k
               //A = half of height
               //n = PI/radius
               //x = distance from center
               //k = half of height
               float new_height = hill.height*0.5f * std::cos(PI / hill.radius * distance) + hill.height*0.5f;

               if (new_height > grid_2d.at(i).at(j).y)
               {
                  grid_2d.at(i).at(j).y = new_height;
                  color_2d.at(i).at(j) = glm::vec3(0.4f + 0.4*(new_height / hill.radius), 0.2f + 0.4*(new_height / hill.radius), 0.04f + 0.5*(new_height / hill.radius));
                  //calculate normal at this location
                  normals_2d.at(i).at(j) = calcNormal(hill, distance, i, j);
               }
            }
         }
      }
   }
   grid = flatten(grid_2d);
   color = flatten(color_2d);
   normals = flatten(normals_2d);
}

std::vector<glm::vec3> TerrainBlock::Builder::flatten(const std::vector<std::vector<glm::vec3>>& vector2d)
{
   std::vector<glm::vec3> new_vector;
   for (int i = 0; i < vector2d.size(); i++)
   {
      for (int j = 0; j < vector2d.front().size(); j++)
      {
         new_vector.emplace_back(vector2d.at(i).at(j));
      }
   }
   return new_vector;
}

///Calculate normals of 3D cos based hill
glm::vec3 TerrainBlock::Builder::calcNormal(Hill hill, float distance, int i, int j)
{
   // To find a 3D vector, the we need a tangent plane of A*cos(sqrt(i^2+j^2)) + k
   // I pretty much re-learned Calculus III to do this

   // using the center of a hill as the new (0,0) coordinate, convert (i,j) to that
   const float x = i - hill.x;
   const float z = j - hill.z;
   const float n = PI / hill.radius;

   // Step 1: Get partial derivatives
   // used wolfram alpha to simplify, https://www.wolframalpha.com/input/?i=differentiate+5*cos(((x%5E2%2Bz%5E2)%5E0.5)+*+8)%2B5
   // in respect to x axis
   // -(5 x sin(sqrt(x^2 + z^2)))/sqrt(x^2 + z^2)
   const float a = -(hill.height * 0.5f * n * x * std::sin(n * sqrt(x * x + z * z))) / std::sqrt(x * x + z * z);

   // in respect to z axis
   // -(5 z sin(sqrt(x^2 + z^2)))/sqrt(x^2 + z^2)
   const float b = -(hill.height * 0.5f * n * z * std::sin(n * sqrt(x * x + z * z))) / std::sqrt(x * x + z * z);

   // Step 2: Tangent plane formula
   // With our plane being y = a(x - x0) + b(z - z0) + y0
   // simplified we get y = ax - c1 + bz - c2 +c3
   // C = ax - y + bz
   // where x0, y0, z0 are the current point against which we are testing
   // means our normal vector to that plane is made of the slope of each of the axis.
   // x axis is sloped by a, y axis is -1, z axis is sloped by b

   return glm::normalize(glm::vec3(a, -1.0f, b));
}

std::vector <GLuint> TerrainBlock::Builder::createEBO(const std::vector<std::vector<GLuint>>& index2d)
{
   // https://stackoverflow.com/questions/5915753/generate-a-plane-with-triangle-strips
   std::vector<GLuint> EBO_indices; // TRIANGLE_STRIP EBO

   for (int row = 0; row < TerrainBlock::CHUNK_LENGTH - 1; row++)
   {
      if ((row & 1) == 0) // even rows
      {
         for (int col = 0; col < TerrainBlock::CHUNK_LENGTH; col++)
         {
            EBO_indices.emplace_back(col + row * TerrainBlock::CHUNK_LENGTH);
            EBO_indices.emplace_back(col + (row + 1) * TerrainBlock::CHUNK_LENGTH);
         }
      }
      else // odd rows
      {
         for (int col = TerrainBlock::CHUNK_LENGTH - 1; col > 0; col--)
         {
            EBO_indices.emplace_back(col + (row + 1) * TerrainBlock::CHUNK_LENGTH);
            EBO_indices.emplace_back(col - 1 + +row * TerrainBlock::CHUNK_LENGTH);
         }
      }
   }
   return EBO_indices;
}

// ------------------------------------------------------------------------------------------------ //
//                                       TERRAIN FUNCTIONS                                          //
// ------------------------------------------------------------------------------------------------ //

void TerrainBlock::Draw(const RenderMode& render_mode) const
{
   ShaderLinker::GetInstance()->SetUniformMat4("model_matrix", m_ModelMatrix);
   m_Terrain.Draw(render_mode);
}
