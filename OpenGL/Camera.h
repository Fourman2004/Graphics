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

const float YAW,PITCH,ZOOM,SENS,SPEED;

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

		void call_Mouse(GLFWwindow* window, double xpos, double ypos)
		{
			float Xposition = static_cast<float>(xpos);
			float Yposition = static_cast<float>(ypos);

			if ()
			{

			}
		}

	private:
		void updateCamera()
		{
			vec3 front;
			front.x = cos(radians(Yaw) * cos(Pitch));
		    front.y = sin(radians(Pitch));
			front.z = sin(radians(Yaw) * cos(Pitch));
			Front = normalize(front);
		}
	};