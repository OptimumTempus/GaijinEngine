#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<fstream>
#include<vector>
#include<iostream>
#include<string>

#include<glm.hpp>
#include<gtc/type_ptr.hpp>

class Shader
{

private:
	GLuint id;

	std::string loadShaderSource(const char* fileName);

	GLuint loadShader(GLenum type, const char* fileName);

	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);

public:
		
	Shader();
	Shader(const char* vertexFile, const char* geometryFile, const char* fragmentFile);
	~Shader();


	void use();
	void unuse();

	void set1i(GLint value, const GLchar* name);

	void set1f(GLfloat value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value,const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);

	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose);

	
};


