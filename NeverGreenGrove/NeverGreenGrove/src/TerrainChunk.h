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

#pragma once

#include "DrawableObject.h"

class TerrainChunk
{
public:
   TerrainChunk();
   DrawableObject m_terrain;

private:
   static const GLuint CHUNK_LENGTH = 256;
   std::vector<std::vector<glm::vec3>> grid_2d;
   std::vector<std::vector<glm::vec3>> color_2d;
   std::vector<glm::vec3> grid;
   std::vector<glm::vec3> color;
   std::vector<GLuint> indices;

   //functions
   void generateVertices();
   void flatTerrain();
   std::vector<glm::vec3> flatten(std::vector<std::vector<glm::vec3>> vector2d);
   std::vector <GLuint> createEBO(std::vector<std::vector<GLuint>> index2d);
};

struct Hill
{
   float height;
   float radius;
   float x;
   float z;

   Hill(float h, float r, float x_pos, float z_pos) : height(h), radius(r), x(x_pos), z(z_pos) {}
};
