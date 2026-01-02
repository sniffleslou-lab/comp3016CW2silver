#include "Camera.h"

Camera::Camera(glm::vec3 startPos) {
	Position = startPos;
	Front = glm::vec3(0.0f, 0.05, -1.05);
	Up = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = -90.0f;
	Pitch = 0.0f;
	MovementSpeed = 3.0f;
	MouseSensitivity = 0.1f;
}
glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Position + Front, Up);
}
//now the controls wo wo woooo
void Camera::ProcessKeyboard(char direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;


	if (direction == 'W') Position += Front * velocity; //foward duh
	if (direction == 'S') Position -= Front * velocity; //backwards
	if (direction == 'A') Position -= glm::normalize(glm::cross(Front, Up)) * velocity;
	if (direction == 'D') Position += glm::normalize(glm::cross(Front, Up)) * velocity;
}
//now mouse
void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
	xoffset += MouseSensitivity;
	yoffset += MouseSensitivity;
	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(direction);
}