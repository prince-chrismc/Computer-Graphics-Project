#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#ifdef _WIN32
// Loads a windows file .obj specialized for DDS textures
bool LoadObjFile(
   const char* path,
   std::vector<glm::vec3>* out_vertices,
   std::vector<glm::vec3>* out_normals,
   std::vector<glm::vec2>* out_uvs
);
#endif // _WIN32

#endif
