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

#pragma once

#include "TerrainBlock.h"
#include "Forest.h"

class Chunk
{
public:
   Chunk() : m_Terrain(), m_Forest(m_Terrain.Get2DGrid()) {}
   ~Chunk() = default;

   static constexpr double ONE_TRANS_UNIT = 128.0 * OBJECTSPACE_TO_REALWORLD;

   void Draw() const { m_Terrain.Draw(RenderMode::TRIANGLES); m_Forest.Draw(); }
   void Translate(const glm::vec3& vec) { m_Terrain.Translate(vec); m_Forest.Translate((1.0f/ OBJECTSPACE_TO_REALWORLD)*vec); }
   float MinDistanceToAnyTree(float from_x, float from_y);

   float GetHeight(float x, float y) {
	   return m_Terrain.Get2DGrid().at(x).at(y).y;
   }

   private:
      TerrainBlock m_Terrain;
      Forest m_Forest;
};
