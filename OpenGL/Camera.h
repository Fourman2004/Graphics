#pragma once
#include <iostream>
#include "glm.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
GLuint screenW = 800, screenH = 600;
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
		mat4 viewMatrix();


		void updateKeyboard(Direction direction, float deltaTime);
		void mouseScroll(float yoffset);

		void mouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

		//void callMouse(GLFWwindow* window, double xpos, double ypos);

		void updateCamera();
	};