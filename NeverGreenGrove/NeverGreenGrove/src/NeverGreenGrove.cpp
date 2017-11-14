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

// Template.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>

#include "GL/glew.h"                            // include GL Extension Wrangler
#include "glm/gtc/matrix_transform.hpp"         //glm::lookAt

#include "GlfwWindow.h"
#include "Shader.h"
#include "ObjLoader.h"

int main()
{
   std::cout << "Welcome to Never Green Grove!" << std::endl;

   // Create a GLFWwindow
   std::shared_ptr<GlfwWindow> window = GlfwWindowFactory::GetInstance()->CreateNewWindow("Never Green Grove - Prepare to get lost!");
   if (!window->IsValid()) // Make sure it exists
   {
      return -1;
   }

   // Set the required callback functions
   /*
   * window->SetKeyCallback(key_callback);
   * window->SetMouseButtonCallback(mouse_callback);
   * window->SetCursorPosCallback(cursor_callback);
   */

   // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
   glewExperimental = GL_TRUE;
   // Initialize GLEW to setup the OpenGL Function pointers
   if (glewInit() != GLEW_OK)
   {
      std::cout << "Failed to initialize GLEW" << std::endl;
      std::cout << "Press 'enter' to exit." << std::endl;
      std::getline(std::cin, std::string());
      return -1;
   }

   // Build and compile our shader program
   VertexShader vertexShader("shaders/vertex.shader");
   FragmentShader fragmentShader("shaders/fragment.shader");
   // make sure they are ready to use
   if (!vertexShader() || !fragmentShader())
   {
      std::cout << "Press 'enter' to exit." << std::endl;
      std::getline(std::cin, std::string());
      return -1;
   }

   auto shaderProgram = ShaderLinker::GetInstance();
   if (!shaderProgram->Link(&vertexShader, &fragmentShader))
   {
      std::cout << "Press 'enter' to exit." << std::endl;
      std::getline(std::cin, std::string());
      return -1;
   }

   // Constant vectors
   const glm::vec3 center(0.0f, 0.0f, 0.0f);
   const glm::vec3 up(0.0f, 1.0f, 0.0f);
   const glm::vec3 eye(3.0f, 15.0f, 9.0f);

   // cube (food) -----------------------------------------------------------------------------------------------------------------------------------
   std::vector<glm::vec3> cube_vertices;
   std::vector<glm::vec3> cube_normals;
   LoadObjFile("assets/Tree2.obj", &cube_vertices, &cube_normals, &std::vector<glm::vec2>()); //read the cube_vertices from the cube.obj file

   GLuint VAO_cube;
   glGenVertexArrays(1, &VAO_cube);
   // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   GLuint cube_vertices_VBO, cube_normals_VBO;
   glGenBuffers(1, &cube_vertices_VBO);
   glGenBuffers(1, &cube_normals_VBO);

   // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
   glBindVertexArray(VAO_cube);

   glBindBuffer(GL_ARRAY_BUFFER, cube_vertices_VBO);
   glBufferData(GL_ARRAY_BUFFER, cube_vertices.size() * sizeof(glm::vec3), &cube_vertices.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(0);

   glBindBuffer(GL_ARRAY_BUFFER, cube_normals_VBO);
   glBufferData(GL_ARRAY_BUFFER, cube_normals.size() * sizeof(glm::vec3), &cube_normals.front(), GL_STATIC_DRAW);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
   glEnableVertexAttribArray(1);

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glBindVertexArray(0); // Unbind VAO_cube (it's always a good thing to unbind any buffer/array to prevent strange bugs)

   // Game loop
   while (! window->ShouldClose())
   {
      // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
      GlfwWindow::TriggerCallbacks();

      // Render
      // Clear the colorbuffer
      glClearColor(0.05f, 0.075f, 0.075f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glm::mat4 view_matrix;
      view_matrix = glm::lookAt(eye, center, up);
      shaderProgram->SetUniformMat4("view_matrix", view_matrix);

      shaderProgram->SetUniformMat4("projection_matrix", window->GetProjectionMatrix());

      // Cube -------------------------------------------------------------------------------------------------------------------------------------
      shaderProgram->SetUniformMat4("model_matrix", glm::scale(glm::mat4(), glm::vec3(0.05)));
      shaderProgram->SetUniformInt("object_color", 0);
      glBindVertexArray(VAO_cube);
      glDrawArrays(GL_TRIANGLES, 0, (GLsizei)cube_vertices.size());
      glBindVertexArray(0);

      window->NextBuffer(); // swap buffers
   }

   return 0;
}

// ------------------------------------------------------------------------------------------------ //
//                                      CALLBACK FUNCTIONS                                        - //
// ------------------------------------------------------------------------------------------------ //
