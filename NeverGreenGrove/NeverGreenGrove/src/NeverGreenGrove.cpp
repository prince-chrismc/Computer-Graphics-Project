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

#include "camera.h"
#include "GlfwWindow.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "DrawableTree.h"

#include "GL/glew.h"                            // include GL Extension Wrangler

#include <string>
#include <iostream>

// Function Declarations
bool SetupShaders();
void PerFrameCalc();

//for camera
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = GlfwWindow::DEFAULT_WIDTH / 2.0f;
float lastY = GlfwWindow::DEFAULT_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;                         // time between current frame and last frame
float lastFrame = 0.0f;                         // time of last frame

int main()
{
   std::cout << "Welcome to Never Green Grove!" << std::endl;

   // Create a GLFWwindow
   auto window = GlfwWindowFactory::GetInstance()->CreateNewWindow("Never Green Grove - Prepare to get lost!");
   if (!window->IsValid()) // Make sure it exists
   {
      return -1;
   }

   // Set the required callback functions
   window->SetFramebufferSizeCallback(framebuffer_size_callback);
   window->SetCursorPosCallback(mouse_callback);
   window->SetScrollCallback(scroll_callback);
   window->SetKeyCallback(key_callback);
   window->CaptureCursor();                     // tell GLFW to capture our mouse

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

   if (!SetupShaders())
   {
      std::cout << "Press 'enter' to exit." << std::endl;
      std::getline(std::cin, std::string());
      return -1;
   }

   auto shaderProgram = ShaderLinker::GetInstance();

   // Tree -----------------------------------------------------------------------------------------------------------------------------------
   DrawableTree tree;

   // Game loop
   while (!window->ShouldClose())
   {
      PerFrameCalc();                           // Per frame time drift calc - MUST be called triggering callbacks
      GlfwWindow::TriggerCallbacks();           // For all windows check callbacks
      camera.moveCamera(deltaTime);

      // Render
      // Clear the colorbuffer
      glClearColor(0.05f, 0.075f, 0.075f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      shaderProgram->SetUniformMat4("view_matrix", camera.GetViewMatrix());
      shaderProgram->SetUniformMat4("projection_matrix", window->GetProjectionMatrix());

      // Tree -------------------------------------------------------------------------------------------------------------------------------------
      tree.Draw();

      window->NextBuffer(); // swap buffers
   }

   return 0;
}

// ------------------------------------------------------------------------------------------------ //
//                                       UTILITY FUNCTIONS                                          //
// ------------------------------------------------------------------------------------------------ //
bool SetupShaders()
{
   VertexShader vertexShader("shaders/vertex.shader");
   FragmentShader fragmentShader("shaders/fragment.shader");
   // make sure they are ready to use
   if (!vertexShader() || !fragmentShader()) return false;

   auto shaderProgram = ShaderLinker::GetInstance();
   if (!shaderProgram->Link(&vertexShader, &fragmentShader)) return false;

   return true;
}

void PerFrameCalc()
{
   float currentFrame = glfwGetTime();
   deltaTime = currentFrame - lastFrame;
   lastFrame = currentFrame;
}

// ------------------------------------------------------------------------------------------------ //
//                                      CALLBACK FUNCTIONS                                        - //
// ------------------------------------------------------------------------------------------------ //
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);

   if (key == GLFW_KEY_W && action == GLFW_PRESS)
      camera.goForward = true;
   if (key == GLFW_KEY_W && action == GLFW_RELEASE)
      camera.goForward = false;

   if (key == GLFW_KEY_S && action == GLFW_PRESS)
      camera.goBackward = true;
   if (key == GLFW_KEY_S && action == GLFW_RELEASE)
      camera.goBackward = false;

   if (key == GLFW_KEY_A && action == GLFW_PRESS)
      camera.goLeft = true;
   if (key == GLFW_KEY_A && action == GLFW_RELEASE)
      camera.goLeft = false;

   if (key == GLFW_KEY_D && action == GLFW_PRESS)
      camera.goRight = true;
   if (key == GLFW_KEY_D && action == GLFW_RELEASE)
      camera.goRight = false;

   if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
      camera.goUp = true;
   if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
      camera.goUp = false;

   if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
      camera.goDown = true;
   if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
      camera.goDown = false;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   // make sure the viewport matches the new window dimensions; note that width and
   // height will be significantly larger than specified on retina displays.
   glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
   //using method from https://learnopengl.com/code_viewer_gh.php?code=src/1.getting_started/7.4.camera_class/camera_class.cpp
   if (firstMouse)
   {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
   }

   float xoffset = xpos - lastX;
   float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

   lastX = xpos;
   lastY = ypos;

   camera.ProcessMouseMovement(xoffset, yoffset);
}

//only used for FOV
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
   camera.ProcessMouseScroll(yoffset);
}
