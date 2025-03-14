#pragma once
#include "main.h"
#include <ext/matrix_transform.hpp>

using namespace glm;

	float radial = 10.0f;
	float mC_speed = 0.5;
	float lastF = 0;
	float currentF = glfwGetTime();
	float deltaT = currentF - lastF;
	mat4 view = mat4(1);
	vec3 CamFront = vec3(0,0,-1);
	vec3 cameraPosition = vec3(0, 0, 3);
	vec3 cameraTarget = vec3(0, 0, 0);
	vec3 cameraDirection = normalize(cameraPosition - cameraTarget);
	vec3 CamY = vec3(0, 1, 0);
	float CamX = static_cast<float>(sin(glfwGetTime()*radial));
	float CamZ = static_cast<float>(cos(glfwGetTime()*radial));
	vec3 cameraRight = normalize(cross(CamY, cameraDirection));
	vec3 camerUp = cross(cameraDirection, cameraRight);
