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

#include "Chunk.h"

class World
{
public:
   World();
   ~World();
   void Draw() const { for (auto chunk : m_Map) { chunk.second->Draw(); } }

   bool HitsAnything(glm::vec3 cam_pos);

   private:

      struct Point {long long x, y; };

      //Compare the coordinates of two Points
      struct PointCmp
      {
         bool operator()(const Point &lhs, const Point &rhs) const
         {
            return (lhs.x < rhs.x) ? true : (lhs.x == rhs.x && lhs.y < rhs.y) ? true : false;
         }
      };


   std::map<Point, std::shared_ptr<Chunk>, PointCmp> m_Map;

};

