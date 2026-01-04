#include "Signature.h"
#include <glm/gtc/type_ptr.hpp>

Signature::Signature() {
	float quadVerticles[] = {
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,

		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerticles), quadVerticles, GL_STATIC_DRAW);

	//pos attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//tex coord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
Signature::~Signature() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
void Signature::Draw(GLuint program, GLuint textureID, const glm::mat4& model) {
	glUseProgram(program);

	//model
	GLuint modelLoc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	//bind 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);
	//draw
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
	

