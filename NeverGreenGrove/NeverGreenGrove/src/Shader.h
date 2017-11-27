/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

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

#include "GL/glew.h"                            // include GL Extension Wrangler
#include "glm/gtc/type_ptr.hpp"                 // glm::value_ptr
#include <string>
#include <mutex>

class Shader abstract
{
   friend class ShaderLinker;
public:
   Shader(const std::string& rel_path);
   ~Shader();

   bool operator()() const { return m_Status; }

protected:
   virtual bool Compile(const std::string& ShaderCode) = 0;

   const std::string m_ShaderRelPath;
   std::string m_ShaderCode;
   bool m_Status;
   GLuint m_Shader;
};

class VertexShader : public Shader
{
public:
   VertexShader(const std::string& rel_path) : Shader(rel_path) { m_Status = Compile(m_ShaderCode); }
   VertexShader(const char* rel_path) : VertexShader(std::string(rel_path)) {}

   bool Compile(const std::string& ShaderCode);
};

class FragmentShader : public Shader
{
public:
   FragmentShader(const std::string& rel_path) : Shader(rel_path) { m_Status = Compile(m_ShaderCode); }
   FragmentShader(const char* rel_path) : FragmentShader(std::string(rel_path)) {}

   bool Compile(const std::string& ShaderCode);
};

class ShaderLinker
{
public:
   ~ShaderLinker() = default;
   ShaderLinker(const ShaderLinker&) = delete;
   ShaderLinker& operator=(const ShaderLinker&) = delete;

   static std::shared_ptr<ShaderLinker> GetInstance() { std::call_once(s_Flag, []() { s_Instance.reset(new ShaderLinker()); }); return s_Instance; }

   bool Link(VertexShader* vertex, FragmentShader* frag);

   GLuint GetUniformLocation(const char* shader_obj) const { return glGetUniformLocation(m_ShaderProgram, shader_obj); }
   GLuint GetAttributeLocation(const char* shader_obj) const { return glGetAttribLocation(m_ShaderProgram, shader_obj); }

   void SetUniformInt(const char* shader_obj, const GLint& i) const { glUniform1i(GetUniformLocation(shader_obj), i); }
   void SetUniformMat4(const char* shader_obj, const glm::mat4& mat) const { glUniformMatrix4fv(GetUniformLocation(shader_obj), 1, GL_FALSE, glm::value_ptr(mat)); }
   void SetUniformVec3(const char* shader_obj, const glm::vec3& vec) { glUniform3fv(GetUniformLocation(shader_obj), 1, glm::value_ptr(vec)); }

private:
   ShaderLinker() { m_ShaderProgram = glCreateProgram(); }

   void AddShader(Shader* NewShader) { glAttachShader(m_ShaderProgram, NewShader->m_Shader); }

   static std::once_flag s_Flag;
   static std::shared_ptr<ShaderLinker> s_Instance;

   GLuint m_ShaderProgram;
};
