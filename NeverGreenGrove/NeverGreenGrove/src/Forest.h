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

#include "MultiDimGrid.hpp"
#include "glm\matrix.hpp"                       //glm::mat4
#include "glm\gtc\matrix_transform.hpp"         //glm::lookAt
#include "glm\gtx\transform2.hpp"               //glm::shear
#include <mutex>
#include <map>
#include <vector>

constexpr float OBJECTSPACE_TO_REALWORLD = 1.0f / 128.0f * 50.7f;

class Forest
{
public:
   Forest(const std::vector<std::vector<glm::vec3>>& grid_2d);
   ~Forest() = default;

   void Draw() const { for (auto tree : m_Map) { tree.second->Draw(); } }
   void Translate(const glm::vec3& vec) { for (auto tree : m_Map) { tree.second->Translate(vec); } }

   bool IsTreeAt(std::size_t x, std::size_t y);

private:
   class DrawableTree abstract
   {
      public:
         DrawableTree() : m_TranslationMatrix(1.0f), m_RotationMatrix(1.0f), m_ScaleMatrix(1.0f) {}

         virtual void Draw() const = 0;
         void Translate(const glm::vec3& vec) { m_TranslationMatrix = glm::translate(m_TranslationMatrix, vec); }
         void Rotate(float angle) { m_RotationMatrix = glm::rotate(m_RotationMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); }

      protected:
         void Scale(glm::vec3 vec) { m_ScaleMatrix = glm::scale(m_ScaleMatrix, vec); }
         void Shear(float deform_x, float deform_z) { m_TranslationMatrix = glm::shearY3D(m_TranslationMatrix, deform_x, deform_z); }

         glm::mat4 m_TranslationMatrix;
         glm::mat4 m_ScaleMatrix;
         glm::mat4 m_RotationMatrix;
   };

   class TreeA;
   class TreeA2;
   class TreeA3;
   class TreeB;
   class TreeB2;
   class TreeFactory;

   struct Point { std::size_t x, y; };

   //Compare the coordinates of two Points
   struct PointCmp
   {
      bool operator()(const Point &lhs, const Point &rhs) const
      {
         return (lhs.x < rhs.x) ? true : (lhs.x == rhs.x && lhs.y < rhs.y) ? true : false;
      }
   };

   std::map<Point, std::shared_ptr<DrawableTree>, PointCmp> m_Map;
   //multidim::Grid<bool, 128, 128, 128> m_ObjectSpace; // https://github.com/coin-au-carre/MultiDimGrid/blob/master/example/01-basic.cpp
   multidim::Grid<float, 128, 128> m_HeightMap;
};
