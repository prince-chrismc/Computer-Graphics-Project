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

#include <map>
#include <memory>
#include <vector>

struct Point { std::size_t x, y; };

typedef Point* PointPtr;
//Compare the x-coordinates of two Point pointers
struct PointCmp
{
   bool operator()(const Point &lhs, const Point &rhs) const
   {
      return lhs.x < rhs.x;
   }
};

template<typename Object>
// This is a 2D grid template to map an Object
class GridMap
{
public:
   GridMap<Object>(std::size_t length) : m_Map() {} // figure how to easly fix size

   const Object& at(std::size_t x, std::size_t y) const { m_Map.at(Point{ x, y } ); }
   void set(std::size_t x, std::size_t y, const Object& obj) { m_Map.emplace(Point{ x, y }, obj); }

private:
   std::map<Point, Object, PointCmp> m_Map;
};

template<typename Object>
class GridVectors
{
public:
   GridVectors<Object>(std::size_t length) : m_Vecs(length, std::vector<Object>(length, Object())) { }

   const Object& at(std::size_t x, std::size_t y) const { m_Vecs.at(x).at(y); }
   void set(std::size_t x, std::size_t y, const Object& obj) { m_Vecs.at(x).at(y) = obj; }

private:
   std::vector<std::vector<Object>> m_Vecs;

   //void FillToSize(std::size_t length);

};

GridMap<float>;
GridVectors<float>;
