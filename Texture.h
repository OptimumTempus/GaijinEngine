#pragma once
#include<gl/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<string>
#include<SOIL2.h>

#include<ft2build.h>
#include FT_FREETYPE_H
#include<map>

#include"Include/glm_libs.h"


class Texture
{


private:
	bool RGBA;
	GLuint id;
	int width;
	int height;
	unsigned int type;
	GLint textureUnit;
public:
	Texture(const char* fileName, GLenum type, GLint texture_unit, bool rgba);
	Texture();

	~Texture();

	GLuint getID() const;

	void bind();
	void unbind();

	GLuint getTextureUnit();


};