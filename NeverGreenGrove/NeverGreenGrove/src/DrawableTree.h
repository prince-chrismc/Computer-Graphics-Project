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

class DrawableTree abstract
{
   public:
      DrawableTree() = default;

      virtual void Draw() = 0;
      void Translate(glm::vec3 vec) { m_ModelMatrix = glm::translate(m_ModelMatrix, vec); }

   protected:
      void Scale(glm::vec3 vec) { m_ModelMatrix = glm::scale(m_ModelMatrix, vec); }
      void Rotate(float angle) { m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)); }
      void Shear(float deform_x, float deform_z) { m_ModelMatrix = glm::shearY3D(m_ModelMatrix, deform_x, deform_z); }

      glm::mat4 m_ModelMatrix;
};

class TreeA : public DrawableTree
{
   public:
      void Draw();

   private:
      class TreeObj
      {
      public:
         ~TreeObj();
         TreeObj(const TreeObj&) = delete;
         TreeObj& operator=(const TreeObj&) = delete;

         static std::shared_ptr<TreeObj> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new TreeObj()); }); return s_Instance; }

         GLuint GetVAO() { return m_VAO; }
         GLsizei GetNumberOfVertices() { return m_NumVertices; }

      private:
         TreeObj();

         GLuint m_VAO;
         GLuint m_Verticies;
         GLuint m_Colors;
         //GLuint m_Normals;
         //GLuint m_Uvs;

         GLsizei m_NumVertices;

         static std::once_flag s_Flag;
         static std::shared_ptr<TreeObj> s_Instance;
      };
};

class TreeA2 : public TreeA
{
public:
   TreeA2() { Scale(glm::vec3(1.0, 1.1, 1.1)); Rotate(90.f); }
};

class TreeA3 : public TreeA
{
public:
   TreeA3() { Shear(-0.25f, 0.1f); }
};

class TreeB : public DrawableTree
{
   public:
      DrawableTree() : m_ModelMatrix(glm::scale(glm::mat4(), glm::vec3(2.5))) {}
      ~DrawableTree() = default;

      void Draw();

   private:
      class TreeObj
      {
      public:
         ~TreeObj();
         TreeObj(const TreeObj&) = delete;
         TreeObj& operator=(const TreeObj&) = delete;

         static std::shared_ptr<TreeObj> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new TreeObj()); }); return s_Instance; }

         GLuint GetVAO() { return m_VAO; }
         GLsizei GetNumberOfVertices() { return m_NumVertices; }

      private:
         TreeObj();

         GLuint m_VAO;
         GLuint m_Verticies;
         GLuint m_Colors;
         //GLuint m_Normals;
         //GLuint m_Uvs;

         GLsizei m_NumVertices;

         static std::once_flag s_Flag;
         static std::shared_ptr<TreeObj> s_Instance;
      };
};

class TreeB2 : public TreeB
{
public:
   TreeB2() { Scale(glm::vec3(1.1, 1.25, 0.9)); Rotate(75.0f); }
};

class TreeFactory
{
   public:
      TreeFactory() = delete;
      static std::unique_ptr<DrawableTree> GetNewTree();
};
