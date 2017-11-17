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

	generateVertices();

	DrawableObject test(grid,color,indices);
	m_terrain = test;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Functions to calculate height and location of hills

void TerrainChunk::generateVertices() {
	//Remember: points are (x,y,z) with 
	//x= width
	//y= height
	//z= depth

	//create a simple flat terrain
	flatTerrain();

	int min_radius = CHUNK_LENGTH / 8;
	int max_radius = CHUNK_LENGTH / 4;
	int inner_length = CHUNK_LENGTH - 2 * min_radius;
	
	float min_height = min_radius / 2.0f;
	float max_height = 100.0f;
	std::vector<Hill> hills;
	int hill_qty;

	//random shuffle
	std::random_device rd;
	std::mt19937 g(rd());

	
	//max hills
	hill_qty = 3 + g() % 7;
	std::vector<float> hill_heights;

	//creates indicies for hill peaks
	std::vector<int> horizontalPeaks;
	std::vector<int> depthPeaks;
	for (int i = 0; i < hill_qty; i++) {
		horizontalPeaks.emplace_back(inner_length / hill_qty + (inner_length / hill_qty)*i);
		depthPeaks.emplace_back(inner_length / hill_qty + (inner_length / hill_qty)*i);
	}
	//shuffle the indicies
	std::shuffle(horizontalPeaks.begin(), horizontalPeaks.end(), g);
	std::shuffle(depthPeaks.begin(), depthPeaks.end(), g);

	/////////////create all the hills

	//Saturate their info, create peaks
	for (int i = 0; i < hill_qty; i++) {
		float tempheight = min_height + g() % (int)(max_height - min_height);
		int max_r = std::min(std::min(std::min((float)horizontalPeaks.at(i), (float)depthPeaks.at(i)), std::min((float)CHUNK_LENGTH - horizontalPeaks.at(i), (float)CHUNK_LENGTH - depthPeaks.at(i))), (float)max_radius);
		float tempradius = min_radius + (g() % max_r);
		grid_2d.at(horizontalPeaks.at(i)).at(depthPeaks.at(i)).y = tempheight;
		Hill newhill(tempheight, tempradius, horizontalPeaks.at(i), depthPeaks.at(i));
		hills.emplace_back(newhill);
		color_2d.at(newhill.x).at(newhill.z) = glm::vec3(0.4f + 0.6*(tempheight / max_height), 0.2f + 0.8*(tempheight / max_height), 0.04f + 0.96*(tempheight / max_height));
	}

	//Change all points inside their radius
	//to find wether a point is in a circle, use https://math.stackexchange.com/questions/198764/how-to-know-if-a-point-is-inside-a-circle
	for (int i = 0; i < CHUNK_LENGTH; i++) {
		for (int j = 0; j < CHUNK_LENGTH; j++) {
			//check every hill
			for (auto hill : hills) {
				float distance = sqrt((i - hill.x)*(i - hill.x) + (j - hill.z)*(j - hill.z));
				if (distance <= hill.radius) {
					//map height to range from height https://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another
					float newheight = (hill.height / hill.radius) * (hill.radius - distance);
					if (newheight > grid_2d.at(i).at(j).y) {
						grid_2d.at(i).at(j).y = newheight;
						color_2d.at(i).at(j) = glm::vec3(0.4f + 0.6*(newheight/max_height), 0.2f + 0.8*(newheight / max_height), 0.04f + 0.96*(newheight / max_height));
					}
				}
			}
		}
	}


	grid = flatten(grid_2d);
	color = flatten(color_2d);
}

//create a simple flat terrain
void TerrainChunk::flatTerrain() {
	GLuint counter = 0;
	std::vector<std::vector<GLuint>> indices_2d;

	for (int i = 0; i < CHUNK_LENGTH; i++) {
		std::vector<glm::vec3> temp_builder;
		std::vector<glm::vec3> temp_color;
		std::vector<GLuint> temp_indices;
		for (int j = 0; j < CHUNK_LENGTH; j++) {
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

