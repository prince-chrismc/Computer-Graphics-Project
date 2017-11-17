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

#include <random>		//mt19937
#include <algorithm>    // std::random_shuffle

#include "TerrainChunk.h"


///generates random terrain
TerrainChunk::TerrainChunk()
{
	//THIS CONSTRUCTOR IS TEMPORARY.
	//only created for testing a simple render


	int counter = 0;
	std::vector<std::vector<GLuint>> indices_2d;

	for (int i = 0; i < CHUNK_HEIGHT; i++) {
		std::vector<GLuint> temp_indices;
		for (int j = 0; j < CHUNK_WIDTH; j++) {
			grid.emplace_back(glm::vec3(i, 0, j));
			color.emplace_back(glm::vec3(1));
			temp_indices.emplace_back(counter);
			counter++;
		}
		indices_2d.emplace_back(temp_indices);
	}
	indicies = createEBO(indices_2d);

	DrawableObject test(grid,color,indicies);
	m_terrain = test;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions to calculate height and location of hills

void TerrainChunk::generateVertices() {
	//Remember: points are (x,y,z) with 
	//x= width
	//y= length
	//z= height

	int min_radius = CHUNK_WIDTH / 8;
	int max_radius = CHUNK_WIDTH / 4;
	int inner_width = CHUNK_WIDTH - 2 * min_radius;
	int inner_depth = CHUNK_HEIGHT - 2 * min_radius;
	
	float min_height = min_radius / 2.0f;
	std::vector<float> all_heights;
	int hill_qty;
	//random shuffle
	std::random_device rd;
	std::mt19937 g(rd());

	//Creates up to 10 hills
	//max hills
	hill_qty = g() % 10;

	//creates indicies for hill peaks
	std::vector<int> horizontalPeaks;
	std::vector<int> depthPeaks;
	for (int i = 0; i < hill_qty; i++) {
		horizontalPeaks.emplace_back(inner_width / hill_qty + min_radius*i);
		depthPeaks.emplace_back(inner_depth / hill_qty + min_radius*i);
	}
	//shuffle the indicies
	//std::random_shuffle(horizontalPeaks.begin(), horizontalPeaks.end(), g());
	//std::random_shuffle(depthPeaks.begin(), depthPeaks.end(), g());

	//create a simple flat terrain
	for (int i = 0; i < CHUNK_HEIGHT; i++) {
		std::vector<glm::vec3> temp_builder;
		for (int j = 0; j < CHUNK_WIDTH; j++) {
				temp_builder.emplace_back(i, j, 0);
		}
		grid_2d.emplace_back(std::move(temp_builder));
	}

	//replace indexed locations by hills
	/*for (int i = 0; i < horizontalPeaks.size(); i++) {
		for (int j = 0; j < depthPeaks.size(); j++) {

			grid_2d.at(i).at(j).z = g() % max_radius;
		}
	}*/

}

std::vector <GLuint> TerrainChunk::createEBO(std::vector<std::vector<GLuint>> index2d)
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

std::vector<glm::vec3> TerrainChunk::flatten(std::vector<std::vector<glm::vec3>> vector2d)
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