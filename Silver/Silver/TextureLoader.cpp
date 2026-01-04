#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

GLuint LoadTexture(const char* filepath) {
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "texture failed to loas : " << filepath << std::endl;
	}
	stbi_image_free(data);
	return textureID;
}