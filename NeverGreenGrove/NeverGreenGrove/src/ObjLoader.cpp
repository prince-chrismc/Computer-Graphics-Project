/*
   This is a modified version of the code provided by the staff of the class
*/

#include <vector>
#include <stdio.h>
#include <string>

#include <glm/glm.hpp>

#include "ObjLoader.h"

#ifdef _WIN32
bool LoadObjFile(const char* path, std::vector<glm::vec3>* out_vertices, std::vector<glm::vec3>* out_normals,
                 std::vector<glm::vec2>* out_uvs)
{
   std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
   std::vector<glm::vec3> temp_vertices;
   std::vector<glm::vec2> temp_uvs;
   std::vector<glm::vec3> temp_normals;

   FILE* file;
   errno_t err = fopen_s(&file, path, "r");
   if (err)
   {
      printf("Impossible to open the file! Are you in the right path ?\n");
      getchar();
      return false;
   }

   while (1)
   {
      char lineHeader[128];
      // read the first word of the line
      int res = fscanf_s(file, "%s", lineHeader, (unsigned int)_countof(lineHeader));

      if (res == EOF) break; // EOF = End Of File. Quit the loop.

      if (strcmp(lineHeader, "v") == 0)
      {
         float x, y, z;
         fscanf_s(file, "%f %f %f\n", &x, &y, &z);
         temp_vertices.emplace_back(x, y, z);
      }
      else if (strcmp(lineHeader, "vt") == 0)
      {
         float x, y;
         fscanf_s(file, "%f %f\n", &x, &y);
         temp_uvs.emplace_back(x, -y); // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
      }
      else if (strcmp(lineHeader, "vn") == 0)
      {
         float x, y, z;
         fscanf_s(file, "%f %f %f\n", &x, &y, &z);
         temp_normals.emplace_back(x, y, z);
      }
      else if (strcmp(lineHeader, "f") == 0)
      {
         unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
         int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
         if (matches != 9)
         {
            printf("File can't be read by our simple parser :-( Try exporting with other options\n");
            return false;
         }

         for (unsigned int index : vertexIndex) { vertexIndices.push_back(index); }
         for (unsigned int uv : uvIndex) { uvIndices.push_back(uv); }
         for (unsigned int normal : normalIndex) { normalIndices.push_back(normal); }
      }
      else
      {
         // Probably a comment, eat up the rest of the line
         char stupidBuffer[1000];
         fgets(stupidBuffer, 1000, file);
      }
   }

   // For each vertex of each triangle
   for (unsigned int i = 0; i < vertexIndices.size(); i++)
   {
      // Get the attributes in draw order thanks to the index
      out_vertices->push_back(temp_vertices.at(vertexIndices.at(i) - 1));
      out_uvs->push_back(temp_uvs.at(uvIndices.at(i) - 1));
      out_normals->push_back(temp_normals.at(normalIndices.at(i) - 1));
   }

   return true;
}
#endif
