#pragma once
#include<gl/glew.h>
#include<GLFW/glfw3.h>

#include<glm.hpp>
#include<vec2.hpp>
#include<vec3.hpp>
#include<vec4.hpp>
#include<mat4x4.hpp>
#include<gtc/type_ptr.hpp>

#include"Shader.h"

class Material
{
private:
	float attenuation;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLint diffuseTex;
	GLint specularTex;

public:
	Material(float attenuation, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex);
	Material();
	~Material();

	void sendToShader(Shader& program);
};