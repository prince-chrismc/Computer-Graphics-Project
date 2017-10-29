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

#include <iostream>
#include <fstream>
#include "Shader.h"

std::once_flag ShaderLinker::s_Flag;
std::shared_ptr<ShaderLinker> ShaderLinker::s_Instance;

Shader::Shader(const std::string& rel_path) : m_ShaderRelPath(rel_path), m_Status(false)
{
   std::ifstream ShaderStream(m_ShaderRelPath, std::ios::in);

   if (ShaderStream.is_open())
   {
      std::string Line = "";
      while (std::getline(ShaderStream, Line))
      {
         m_ShaderCode += "\n" + Line;
      }
      ShaderStream.close();
   }
   else
   {
      printf("Impossible to open %s. Are you in the right directory ?\n", m_ShaderRelPath.c_str());
      std::getline(std::cin, std::string());
      return;
   }
}

Shader::~Shader()
{
   glDeleteShader(m_Shader); //free up memory
}

bool VertexShader::Compile(const std::string& ShaderCode)
{
   m_Shader = glCreateShader(GL_VERTEX_SHADER);
   char const * VertexSourcePointer = ShaderCode.c_str();
   glShaderSource(m_Shader, 1, &VertexSourcePointer, NULL);
   glCompileShader(m_Shader);

   // Check for compile time errors
   GLint success;
   GLchar infoLog[512];
   glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(m_Shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      return false;
   }
   return true;
}

bool FragmentShader::Compile(const std::string & ShaderCode)
{
   m_Shader = glCreateShader(GL_FRAGMENT_SHADER);
   char const * FragmentSourcePointer = ShaderCode.c_str();
   glShaderSource(m_Shader, 1, &FragmentSourcePointer, NULL);
   glCompileShader(m_Shader);

   // Check for compile time errors
   GLint success;
   GLchar infoLog[512];
   glGetShaderiv(m_Shader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(m_Shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      return false;
   }
   return true;
}

bool ShaderLinker::Link(VertexShader* vertex, FragmentShader* frag)
{
   AddShader(vertex);
   AddShader(frag);

   glLinkProgram(m_ShaderProgram);

   // Check for linking errors
   GLint success;
   GLchar infoLog[512];
   glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &success);
   if (!success) {
      glGetProgramInfoLog(m_ShaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
      return false;
   }

   glUseProgram(m_ShaderProgram);
   return true;
}
