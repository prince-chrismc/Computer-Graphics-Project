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

template<typename Object>
// This is a 2D grid template to map an Object
class GridMap
{
public:
   GridMap<Object>(std::size_t length) : m_Map() {}

   const Object& at(std::size_t x, std::size_t y) const { m_Map.at(std::make_pair(x, y)); }
   void set(std::size_t x, std::size_t y, const Object& obj) { m_Map.emplace(std::make_pair(x, y), obj); }

private:
   std::map<std::pair<std::size_t, std::size_t>, Object> m_Map;
};


//class GridPtr
//{
//public:
//   Grid();
//   ~Grid();
//
//private:
//   std::map<std::pair<int, int>, std::shared_ptr<Object>> m_Map
//};

GridMap<float>;