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

#include "GLFW/glfw3.h"    // include GLFW helper library
#include "glm/glm.hpp"     // include GLM library

class GlfwWindow
{
   public:
      GlfwWindow(const char* title, const int& width, const int& height);
      ~GlfwWindow();

      bool operator()() const { return m_window != nullptr; } // Make sure windows exists
      void operator++() { glfwSwapBuffers(m_window); }  // Swap the screen buffers
      bool operator~() const { return glfwWindowShouldClose(m_window); } // window should close

      const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

      // Allow the required callback functions
      GLFWkeyfun         SetKeyCallback(GLFWkeyfun cbfun) { return glfwSetKeyCallback(m_window, cbfun); }
      GLFWmousebuttonfun SetMouseButtonCallback(GLFWmousebuttonfun cbfun) { return glfwSetMouseButtonCallback(m_window, cbfun); }
      GLFWcursorposfun   SetCursorPosCallback(GLFWcursorposfun cbfun) { return glfwSetCursorPosCallback(m_window, cbfun); }
      GLFWwindowsizefun  SetWindowSizeCallback(GLFWwindowsizefun cbfun) { return glfwSetWindowSizeCallback(m_window, cbfun); } // already handled

      // Default window dimensions
      static const GLuint DEFAULT_WIDTH = 800, DEFAULT_HEIGHT = 600;

   private:
      GLFWwindow* m_window;
      glm::mat4   m_Projection;

      void window_callback(GLFWwindow* window, int width, int height);
};

