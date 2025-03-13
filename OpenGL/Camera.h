#pragma once
#include "main.h"
#include <ext/matrix_transform.hpp>

using namespace glm;


	vec3 cameraPosition = vec3(0, 0, 3);
	vec3 cameraTarget = vec3(0, 0, 0);
	vec3 cameraDirection = normalize(cameraPosition - cameraTarget);
	vec3 CamY = vec3(0,1,0);
	vec3 CamX = vec3(1,0, 0);
	vec3 CamZ = vec3(0, 0, 1);
	vec3 cameraRight = normalize(cross(CamY, cameraDirection));
	vec3 camerUp = cross(cameraDirection, cameraRight);
	mat4 view = lookAt(CamX,CamY,CamZ);
