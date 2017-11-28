/*
      Using camera from
      https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h

      This code has been lightly refactored to match with the rest of the code from the project.
*/

#pragma once

#include "GL\glew.h"
#include "glm\vec3.hpp"
#include "glm\mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"         //glm::lookAt
#include <iostream>

// Default camera values
const float YAW        = -90.0f;
const float PITCH      =  0.0f;
const float SPEED      =  10.0f;
const float SENSITIVTY =  0.1f;
const float ZOOM       =  45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
   //public direction booleans
   bool goForward, goBackward, goRight, goLeft, goUp, goDown;
   bool	godMode;
   bool sprint;
   // Constructor with vectors
   Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
   {
      Position = position;
      WorldUp = up;
      Yaw = yaw;
      Pitch = pitch;
      goForward = goBackward = goRight = goLeft = goUp = goDown = false;
	  godMode = true;
	  sprint = false;
	  updateCameraVectors();
   }

   // Constructor with scalar values
   Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
   {
      Position = glm::vec3(posX, posY, posZ);
      WorldUp = glm::vec3(upX, upY, upZ);
      Yaw = yaw;
      Pitch = pitch;
      goForward = goBackward = goRight = goLeft = goUp = goDown = false;
	  godMode = true;
	  sprint = false;
      updateCameraVectors();
   }

   // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
   glm::mat4 GetViewMatrix()
   {
      return glm::lookAt(Position, Position + Front, Up);
   }

   glm::vec3 GetPos() {
      return Position;
   }

   void moveCamera(float deltaTime, float height)
   {
	   float velocity = MovementSpeed * deltaTime;
	   if (sprint) { velocity *= 2.0f; }
      if (!godMode) {
		  //normal mode
		  if (goForward)
			  Position += Front * velocity;
		  if (goBackward)
			  Position -= Front * velocity;
		  if (goLeft)
			  Position -= Right * velocity;
		  if (goRight)
		      Position += Right * velocity;
		  Position.y = height;
		}
	  else {
		  //godmode
		  velocity *= 7.0f;
		  if (goForward)
			  Position += Front * velocity;
		  if (goBackward)
			  Position -= Front * velocity;
		  if (goLeft)
			  Position -= Right * velocity;
		  if (goRight)
			  Position += Right * velocity;
		  if (goUp)
			  Position += Up * velocity;
		  if (goDown)
			  Position -= Up * velocity;
	  }
   }

   // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
   void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
   {
      xoffset *= MouseSensitivity;
      yoffset *= MouseSensitivity;

      Yaw += xoffset;
      Pitch += yoffset;

      // Make sure that when pitch is out of bounds, screen doesn't get flipped
      if (constrainPitch)
      {
         if (Pitch > 89.0f)
            Pitch = 89.0f;
         if (Pitch < -89.0f)
            Pitch = -89.0f;
      }

      // Update Front, Right and Up Vectors using the updated Eular angles
      updateCameraVectors();
   }

   // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
   void ProcessMouseScroll(float yoffset)
   {
      if (Zoom >= 1.0f && Zoom <= 45.0f)
         Zoom -= yoffset;
      if (Zoom <= 1.0f)
         Zoom = 1.0f;
      if (Zoom >= 45.0f)
         Zoom = 45.0f;
   }

private:
   // Camera Attributes
   glm::vec3 Position;
   glm::vec3 Front;
   glm::vec3 Up;
   glm::vec3 Right;
   glm::vec3 WorldUp;
   // Eular Angles
   float Yaw;
   float Pitch;
   // Camera options
   float MovementSpeed;
   float MouseSensitivity;
   float Zoom;


   // Calculates the front vector from the Camera's (updated) Eular Angles
   void updateCameraVectors()
   {
      // Calculate the new Front vector
      glm::vec3 front;
      front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
      front.y = sin(glm::radians(Pitch));
      front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
      Front = glm::normalize(front);
      // Also re-calculate the Right and Up vector
      Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
      Up = glm::normalize(glm::cross(Right, Front));
		std::cout << "\r" << std::flush << /*"Camera yaw: " << Yaw << "\tCamera Pitch: " << Pitch <<*/ "\tPosition(x,y,z): " << Position.x << ", " << Position.y << ", " << Position.z;
	
   }
};
