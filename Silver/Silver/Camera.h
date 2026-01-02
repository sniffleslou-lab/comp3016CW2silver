#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;

	float Yaw;	
	float Pitch;
	float MovementSpeed;
	float MouseSensitivity;

	Camera(glm::vec3 startPos);
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(char direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset);
};