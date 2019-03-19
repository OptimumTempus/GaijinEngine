#pragma once
#include<iostream>
#include<string>
#include<SOIL2.h>
#include<GL/glew.h>

namespace Utils
{
	class LoadTexture
	{
	public:
		LoadTexture(const char* filename);
		GLuint getTex();
	private:
		GLuint tex;
	};
}