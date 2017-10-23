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

#include "GlfwWindow.h"
#include "glm/gtc/matrix_transform.hpp"

GlfwWindow::GlfwWindow(const char* title, const int& width, const int& height) : m_window(nullptr), m_Projection()
{
   // Init GLFW
   std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
   glfwInit();
   // Set all the required options for GLFW
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   // try to create window
   m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
   if (m_window == nullptr)
   {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      return;
   }

   // select new window
   glfwMakeContextCurrent(m_window);

   // get frame bug from GLFW notify GL and calc Projection Matrix
   {
      int width, height;
      glfwGetFramebufferSize(m_window, &width, &height);

      glViewport(0, 0, width, height);
      m_Projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.0f, 100.0f);
   }
}


GlfwWindow::~GlfwWindow()
{
   // Terminate GLFW, clearing any resources allocated by GLFW.
   glfwTerminate();
}


void GlfwWindow::window_callback(GLFWwindow* window, int width, int height)
{
   // notify GL and calc Projection Matrix using new size
   glViewport(0, 0, width, height);
   m_Projection = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.0f, 100.0f);
}
