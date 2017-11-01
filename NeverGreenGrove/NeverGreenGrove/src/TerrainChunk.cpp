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

#include <random>

#include "TerrainChunk.h"


///generates random terrain
TerrainChunk::TerrainChunk() : m_terrain()
{
	//Remember: points are (x,y,z) with 
	//x= width
	//y= length
	//z= height

	int hill_qty;
	//random shuffle
	std::random_device rd;
	std::mt19937 g(rd());

	//Creates up to 10 hills (temporarily)
	hill_qty = g() % 10;
	for (int i = 0; i < CHUNK_HEIGHT; i++) {
		std::vector<glm::vec3> temp_builder;
		for (int j = 0; j < CHUNK_WIDTH; j++) {
			temp_builder.emplace_back(glm::vec3(i, j, 0));
		}
	}

}