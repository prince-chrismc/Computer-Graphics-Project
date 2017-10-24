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

#include <vector>
#include <memory>

#include "GLFW/glfw3.h"    // include GLFW helper library
#include "glm/glm.hpp"     // include GLM library

class GlfwWindow
{
friend class GlfwWindowFactory;

   public:
      GlfwWindow(const char* title, const int& width, const int& height);

      constexpr bool IsValid() const { return m_window != nullptr; } // Make sure windows exists
      void NextBuffer() { glfwSwapBuffers(m_window); }  // Swap the screen buffers
      bool ShouldClose() const { return glfwWindowShouldClose(m_window); } // window should close

      const glm::mat4& GetProjectionMatrix() const { return m_Projection; }

      // Allow the required callback functions
      GLFWkeyfun         SetKeyCallback(GLFWkeyfun cbfun) { return glfwSetKeyCallback(m_window, cbfun); }
      GLFWmousebuttonfun SetMouseButtonCallback(GLFWmousebuttonfun cbfun) { return glfwSetMouseButtonCallback(m_window, cbfun); }
      GLFWcursorposfun   SetCursorPosCallback(GLFWcursorposfun cbfun) { return glfwSetCursorPosCallback(m_window, cbfun); }

      // Default window dimensions
      static const GLuint DEFAULT_WIDTH = 800, DEFAULT_HEIGHT = 600;

   private:
      GLFWwindow* m_window;
      glm::mat4   m_Projection;

      void UpdateFromResize(const int& width, const int& height);
      GLFWwindowsizefun  SetWindowSizeCallback(GLFWwindowsizefun cbfun) { return glfwSetWindowSizeCallback(m_window, cbfun); }
};


class GlfwWindowFactory
{
   public:
      ~GlfwWindowFactory() { glfwTerminate(); for (GlfwWindow* win : m_Windows) { delete win; } m_Windows.clear(); }
      static GlfwWindowFactory& GetInstance() { static GlfwWindowFactory instance; return instance; }
      GlfwWindow* CreateNewWindow(const char* title, const int& width, const int& height) { m_Windows.push_back(new GlfwWindow(title, width, height)); return m_Windows.back(); }
      GlfwWindow* FindWindow(GLFWwindow* window){ for(GlfwWindow* win : m_Windows) { if(win->m_window == window) return win; } return nullptr; }

   private:
      GlfwWindowFactory() {};

      std::vector<GlfwWindow*> m_Windows;
};
