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

#include "RenderMode.h"
#include "Texture.h"
#include "glm\vec3.hpp"
#include "glm\matrix.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <vector>
#include <mutex>

class TerrainBlock
{
friend class Chunk;
   public:
      TerrainBlock::TerrainBlock() : m_Builder(), m_Terrain(m_Builder.GetVerticies(), m_Builder.GetColors(), m_Builder.GetNormals(), m_Builder.GetIndices(), m_Builder.GetUVs()) {}
      void Draw(const RenderMode& render_mode) const;
      void Translate(const glm::vec3& vec) { m_ModelMatrix = glm::translate(m_ModelMatrix, 2.505f*vec); }

      std::vector<std::vector<glm::vec3>> Get2DGrid() { return m_Builder.Get2DGrid(); }
      static constexpr GLuint CHUNK_LENGTH = 128;

   private:
      class TerrainTexture
      {
         public:
            ~TerrainTexture() = default;
            TerrainTexture(const TerrainTexture&) = delete;
            TerrainTexture& operator=(const TerrainTexture&) = delete;

            static std::shared_ptr<TerrainTexture> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new TerrainTexture()); }); return s_Instance; }

            const GLuint GetTexture(int i) const { return m_Texture.getTexture(i); }

         private:
            TerrainTexture() : m_Texture("assets/dirt.jpg", "assets/grass.jpg" ) {}

            Texture m_Texture;

            static std::once_flag s_Flag;
            static std::shared_ptr<TerrainTexture> s_Instance;
      };

      class DrawableTerrain
      {
         public:
            DrawableTerrain(const std::vector<glm::vec3> verticies, const std::vector<glm::vec3> colors, const std::vector<glm::vec3> normals, const std::vector<GLuint> indicies, const std::vector<glm::vec2> uvs) ;
            ~DrawableTerrain();

            void Draw(const RenderMode& render_mode) const;

         private:
            GLuint m_VAO;
            GLuint m_Verticies;
            GLuint m_Colors;
            GLuint m_Indicies;
            GLuint m_Normals;
            GLuint m_UVs;

            GLsizei m_NumVertices;
            GLsizei m_NumIndicies;
      };

      struct Hill
      {
         Hill(float h, float r, float x_pos, float z_pos) : height(h), radius(r), x(x_pos), z(z_pos) {}

         float height;
         float radius;
         float x;
         float z;
      };

      class Builder
      {
      public:
         Builder() { GenerateVertices(); }
         ~Builder() = default;

         std::vector<std::vector<glm::vec3>> Get2DGrid() { return grid_2d; }
         std::vector<glm::vec3> GetVerticies() { return grid; }
         std::vector<glm::vec3> GetColors() { return color; }
         std::vector<glm::vec3> GetNormals() { return normals; }
         std::vector<glm::vec2> GetUVs() { return UVs; }
         std::vector<GLuint> GetIndices() { return indices; }

      private:
         void BuildFlatTerrain();
         void GenerateVertices();

         static std::vector<glm::vec3> flatten(const std::vector<std::vector<glm::vec3>>& vector2d);
         static glm::vec3 calcNormal(Hill hill, float distance, int i, int j);
         static std::vector <GLuint> createEBO(const std::vector<std::vector<GLuint>>& index2d);

         std::vector<std::vector<glm::vec3>> grid_2d;
         std::vector<std::vector<glm::vec3>> color_2d;
         std::vector<std::vector<glm::vec3>> normals_2d;
         std::vector<glm::vec2> UVs;
         std::vector<glm::vec3> normals;
         std::vector<glm::vec3> grid;
         std::vector<glm::vec3> color;
         std::vector<GLuint> indices;
      };

      Builder m_Builder;
      DrawableTerrain m_Terrain;
      glm::mat4 m_ModelMatrix;
};
