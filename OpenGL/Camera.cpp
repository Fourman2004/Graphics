#include "Camera.h"

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