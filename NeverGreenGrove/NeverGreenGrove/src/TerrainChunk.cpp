/*
MIT License

Copyright (c) 2017 Daniel Privorotsky, privorotskyd(at)gmail(dot)com

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

#include "TerrainChunk.h"
#include "Shader.h"
#include <random>                               //mt19937
#include <algorithm>                            // std::random_shuffle
#include <cmath>
#include <glm\common.hpp>                       // clamp

/// generates random terrain
TerrainChunk::TerrainChunk()
{
   // THIS CONSTRUCTOR IS TEMPORARY.
   // only created for testing a simple render

   generateVertices();

   DrawableObject test(grid, color, indices);
   m_terrain = test;
}

void TerrainChunk::Draw(const RenderMode& render_mode) const
{
   ShaderLinker::GetInstance()->SetUniformMat4("model_matrix", glm::mat4(1.0f));
   m_terrain.Draw(render_mode);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions to calculate height and location of hills

void TerrainChunk::generateVertices() {
   // Remember: points are (x,y,z) with
   // x = width
   // y = height
   // z = depth

   // create a simple flat terrain
   flatTerrain();

   constexpr int MIN_RADIUS = CHUNK_LENGTH / 8;
   constexpr int MAX_RADIUS = CHUNK_LENGTH / 4;
   constexpr int INNER_LENGTH = CHUNK_LENGTH - 2 * MIN_RADIUS;

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
      const float temp_height = MIN_HEIGHT + gen() % (int)(MAX_HEIGHT - MIN_HEIGHT);
      const int max_r = std::min( { (float)horizontal_peaks.at(i), (float)depth_peaks.at(i), (float)CHUNK_LENGTH - horizontal_peaks.at(i), (float)CHUNK_LENGTH - depth_peaks.at(i), (float)MAX_RADIUS });
      const float temp_radius = MIN_RADIUS + (gen() % max_r);

      grid_2d.at(horizontal_peaks.at(i)).at(depth_peaks.at(i)).y = temp_height;
      Hill new_hill(temp_height, temp_radius, horizontal_peaks.at(i), depth_peaks.at(i));
      hills.emplace_back(new_hill);
      color_2d.at(new_hill.x).at(new_hill.z) = glm::vec3(0.4f + 0.6*(temp_height / MAX_HEIGHT), 0.2f + 0.8*(temp_height / MAX_HEIGHT), 0.04f + 0.96*(temp_height / MAX_HEIGHT));
   }

   // Change all points inside their radius
   // to find wether a point is in a circle, use https://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
   for (int i = 0; i < CHUNK_LENGTH; i++)
   {
      for (int j = 0; j < CHUNK_LENGTH; j++)
      {
         //check every hills
         for (auto hill : hills) {
            float distance = sqrt((i - hill.x)*(i - hill.x) + (j - hill.z)*(j - hill.z));
            if (distance <= hill.radius)
            {

               // Using Logistic (Sigmoid) function: https://en.wikipedia.org/wiki/Logistic_function
               // clamp multiplier to 1
               float multiplier = ((hill.radius - distance) / hill.radius * 3 > 1) ? 1 : (hill.radius - distance) / hill.radius * 3;
               float new_height = (hill.height / (1 + std::exp(-0.1*(hill.radius - distance - hill.radius*0.5)))) * multiplier;

               if (new_height > grid_2d.at(i).at(j).y)
               {
                  grid_2d.at(i).at(j).y = new_height;
                  color_2d.at(i).at(j) = glm::vec3(0.4f + 0.6*(new_height / MAX_HEIGHT), 0.2f + 0.8*(new_height / MAX_HEIGHT), 0.04f + 0.96*(new_height / MAX_HEIGHT));
               }
            }
            // prevent spikes on hills
            if (i == hill.x && j == hill.z)
            {
               grid_2d.at(i).at(j).y = grid_2d.at(i - 1).at(j).y;
            }
         }
      }
   }

   grid = flatten(grid_2d);
   color = flatten(color_2d);
}

//create a simple flat terrain
void TerrainChunk::flatTerrain()
{
   GLuint counter = 0;
   std::vector<std::vector<GLuint>> indices_2d;

   for (int i = 0; i < CHUNK_LENGTH; i++)
   {
      std::vector<glm::vec3> temp_builder;
      std::vector<glm::vec3> temp_color;
      std::vector<GLuint> temp_indices;
      for (int j = 0; j < CHUNK_LENGTH; j++)
      {
         temp_builder.emplace_back(i, 0, j);
         temp_indices.emplace_back(counter++);
         //brownish color
         temp_color.emplace_back(glm::vec3(0.4f, 0.2f, 0.04f));
      }
      grid_2d.emplace_back(temp_builder);
      color_2d.emplace_back(temp_color);
      indices_2d.emplace_back(temp_indices);
   }
   //grid = flatten(grid_2d);
   indices = createEBO(indices_2d);
}

std::vector <GLuint> TerrainChunk::createEBO(const std::vector<std::vector<GLuint>>& index2d)
{
   std::vector<GLuint> EBO_indices;
   for (int i = 0; i < index2d.size() - 1; i++)
   {
      for (int j = 0; j < index2d.front().size() - 1; j++)
      {
         //triangle 1
         EBO_indices.emplace_back(index2d.at(i + 1).at(j));
         EBO_indices.emplace_back(index2d.at(i).at(j));
         EBO_indices.emplace_back(index2d.at(i).at(j + 1));

         //triangle 2
         EBO_indices.emplace_back(index2d.at(i).at(j + 1));
         EBO_indices.emplace_back(index2d.at(i + 1).at(j + 1));
         EBO_indices.emplace_back(index2d.at(i + 1).at(j));
      }
   }
   return EBO_indices;
}

std::vector<glm::vec3> TerrainChunk::flatten(const std::vector<std::vector<glm::vec3>>& vector2d)
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

