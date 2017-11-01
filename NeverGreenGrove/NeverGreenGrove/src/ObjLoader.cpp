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
         glm::vec3 vertex;
         fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
         temp_vertices.push_back(vertex);
      }
      else if (strcmp(lineHeader, "vt") == 0)
      {
         glm::vec2 uv;
         fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
         uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
         temp_uvs.push_back(uv);
      }
      else if (strcmp(lineHeader, "vn") == 0)
      {
         glm::vec3 normal;
         fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
         temp_normals.push_back(normal);
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

         for (unsigned int index : vertexIndex) { vertexIndices.emplace_back(index); }
         for (unsigned int uv : uvIndex) { vertexIndices.emplace_back(uv); }
         for (unsigned int normal : normalIndex) { vertexIndices.emplace_back(normal); }
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
      // Get the indices of its attributes
      unsigned int vertexIndex = vertexIndices[i];
      unsigned int uvIndex = uvIndices[i];
      unsigned int normalIndex = normalIndices[i];

      // Get the attributes thanks to the index
      glm::vec3 vertex = temp_vertices[vertexIndex - 1];
      glm::vec2 uv = temp_uvs[uvIndex - 1];
      glm::vec3 normal = temp_normals[normalIndex - 1];

      // Put the attributes in buffers
      out_vertices->push_back(vertex);
      out_uvs->push_back(uv);
      out_normals->push_back(normal);
   }

   return true;
}
#endif
