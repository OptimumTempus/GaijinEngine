#pragma once

#include<iostream>
#include<vector>
#include<gtc/matrix_transform.hpp>

#include"Texture.h"
#include"Vertex.h"
#include"Material.h"
#include"Shader.h"
#include"Primitive.h"

#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<random>




class Mesh
{
protected:
	bool wireFrame = false;

	bool debugInfo;

	unsigned numOfVertices;
	unsigned numOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;
	

	bool loadModelFromFile(std::string fileName);

	void initVAO(Vertex * vertexArray, const unsigned & numOfVertices, GLuint * indexArray, const unsigned & numOfIndices);

	void initVAOWithPrim(Primitive * primitive);


	void updateUniforms(Shader* shader);

	void updateModelMatrix();
	const float moveSpeed = 3.f;
public:
	Mesh();
	Mesh(Vertex * vertexArray, const unsigned & numOfVertices, GLuint * indexArray, const unsigned & numOfIndices, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	Mesh(Primitive* primitive, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));
	Mesh(std::string fileName, glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f), glm::vec3 scale = glm::vec3(1.f));

	~Mesh();

	Vertex vertices[4096];
	GLuint indices[4096];

	inline void toggleWireFrame()
	{
		wireFrame = !wireFrame;
	};

	inline glm::vec3 getPosition()
	{
		return position;
	};

	void setPosition(const glm::vec3 position);
	void setRotation(const glm::vec3 rotation);
	void setScale(const glm::vec3 scale);

	void move(const glm::vec3 position);
	void move(const float & dt, const int direction);
	void rotate(const glm::vec3 rotation);
	void _scale(const glm::vec3 scale);


	void render(Shader* shader);

};
