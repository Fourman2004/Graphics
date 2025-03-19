#pragma once
#include "main.h"
#include <ext/matrix_transform.hpp>

using namespace glm;

enum Direction
{
	FORWARD,
	BACKWARD
	, LEFT
	, RIGHT
};

float currentF= static_cast<float>(glfwGetTime());
bool mouse;
const float YAW = -90,
PITCH = 0,ZOOM = 45,SENS = 0.1,SPEED = 2.5;
unsigned int screenW = 800, screenH = 600;
float lastX = screenW / 2.0f;
float lastY = screenH / 2.0f;

	class Camera
	{
	public:
		vec3 Pos,Front,Up,Down,Right,Wup;
		float Yaw, Pitch, Speed, Sensitivity, Zoom;

		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Speed(SPEED), Sensitivity(SENS), Zoom(ZOOM)
		{
			Pos = position;
			Wup = up;
			Yaw = yaw;
			Pitch = pitch;
			updateCamera();
		}

		Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), Speed(SPEED), Sensitivity(SENS), Zoom(ZOOM)
		{
			Pos = glm::vec3(posX, posY, posZ);
			Wup = glm::vec3(upX, upY, upZ);
			Yaw = yaw;
			Pitch = pitch;
			updateCamera();
		}
		mat4 viewMatrix()
		{
			return lookAt(Pos, Pos + Front, Up);
		}


		void updateKeyboard(Direction direction, float deltaTime)
		{
			float velocity = Speed * deltaTime;
			switch (direction)
			{
			case FORWARD:
				
				Pos += Front * velocity;
				break;
			case BACKWARD:
				Pos -= Front * velocity;
				
				break;
			case LEFT:
				Pos -= Right * velocity;
				break;
			case RIGHT:
				Pos -= Right * velocity;	
				break;
			}
		}
		void mouseScroll(float yoffset)
		{
			Zoom -= (float)yoffset;
			if (Zoom < 1.0f)
				Zoom = 1.0f;
			if (Zoom > 45.0f)
				Zoom = 45.0f;
		}

		void mouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
		{
			xoffset *= Sensitivity;
			yoffset *= Sensitivity;
			Yaw = xoffset;
			Pitch = yoffset;
			if (constrainPitch)
			{
				if (Pitch > 89)
					Pitch = 89;
				if (Pitch < -89)
					Pitch = -89;
					updateCamera();
			}

		}

		/*void callMouse(GLFWwindow* window, double xpos, double ypos)
		{
			float Xposition = static_cast<float>(xpos);
			float Yposition = static_cast<float>(ypos);

			if (mouse)
			{
				lastX = Xposition;
				lastY = Yposition;
				mouse = false;
			}
			float Xoff, Yoff;
			Xoff = Xposition - lastX;
			Yoff = Yposition - lastX;
			lastX = Xposition;
			lastY = Yposition;
			mouseMovement(Xoff,Yoff);
		}*/

		void updateCamera()
		{
			vec3 front;
			front.x = cos(radians(Yaw) * cos(Pitch));
		    front.y = sin(radians(Pitch));
			front.z = sin(radians(Yaw) * cos(Pitch));
			Front = normalize(front);
		}
	};