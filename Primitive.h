#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<vector>
#include"Vertex.h"

class Primitive
{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;

	Vertex vert[4096];
	GLuint indi[4096];

public:
	Primitive();
	virtual ~Primitive();

	//Functions
	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices);

	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline std::vector<Vertex> returnVert() { return this->vertices; };
	inline std::vector<GLuint> returnIndi() { return this->indices; };
	inline Vertex returnVerts(int position) { return this->vert[position]; };
	inline GLuint returnIndis(int position) { return this->indi[position]; };
	inline int returnVertSize() { return (sizeof(vert) / sizeof(*vert)); };
	inline int returnIndiSize() { return (sizeof(indi) / sizeof(*indi)); };
	inline const unsigned getNumOfVertices() { return this->vertices.size(); }
	inline const unsigned getNumOfIndices() { return this->indices.size(); }
};

class Triangle : public Primitive
{
public:
	Triangle();
};

class Quad : public Primitive
{
public:
	Quad();
};

class Floor : public Primitive
{
public:
	Floor();
};

class Pyramid : public Primitive
{
public:
	Pyramid();
};

class Cube : public Primitive
{
public:
	Cube();
};

class Box : public Primitive
{
public:
	Box();
};


class Butt : public Primitive
{
public:
	Butt();
};

class Test : public Primitive
{
public:
	Test();
};