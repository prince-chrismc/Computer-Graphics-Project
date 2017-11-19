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

#include "glm\matrix.hpp"
#include "glm/gtc/matrix_transform.hpp"         //glm::lookAt
#include "glm\gtx\transform2.hpp"
#include "gl\glew.h"
#include <mutex>

class TreeObjA
{
   public:
      ~TreeObjA();
      TreeObjA(const TreeObjA&) = delete;
      TreeObjA& operator=(const TreeObjA&) = delete;

      static std::shared_ptr<TreeObjA> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new TreeObjA()); }); return s_Instance; }

      GLuint GetVAO() { return m_VAO; }
      GLsizei GetNumberOfVertices() { return m_NumVertices; }

   private:
      TreeObjA();

      GLuint m_VAO;
      GLuint m_Verticies;
      GLuint m_Colors;
      //GLuint m_Normals;
      //GLuint m_Uvs;

      GLsizei m_NumVertices;

      static std::once_flag s_Flag;
      static std::shared_ptr<TreeObjA> s_Instance;
};

class DrawableTree abstract
{
   public:
      DrawableTree() = default;

      void Draw();
      void Translate(glm::vec3 vec) { m_ModelMatrix = glm::translate(m_ModelMatrix, vec); }

   protected:
      void Scale(glm::vec3 vec) { m_ModelMatrix = glm::scale(m_ModelMatrix, vec); }
      void Rotate(float angle) { m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); }
      void Shear(float deform_x, float deform_z) { m_ModelMatrix = glm::shearY3D(m_ModelMatrix, deform_x, deform_z); }

   private:
      glm::mat4 m_ModelMatrix;
};


class TreeA1 : public DrawableTree
{
   public:
      TreeA1() = default;
};

class TreeA2 : public DrawableTree
{
public:
   TreeA2() { Scale(glm::vec3(1.0, 1.1, 1.1)); Rotate(90.f); }
};

class TreeA3 : public DrawableTree
{
public:
   TreeA3() { Shear(-0.25f, 0.1f); }
};

class TreeFactory
{
   public:
      TreeFactory() = delete;
      static std::unique_ptr<DrawableTree> GetNewTree();
};
