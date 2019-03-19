#include "Primitive.h"


Primitive::Primitive()
{
}
 
Primitive::~Primitive()
{
}

void Primitive::set(const Vertex * vertices, const unsigned numOfVertices, const GLuint * indices, const unsigned numOfIndices)
{
	for (size_t i = 0; i < numOfVertices; i++)
	{
		this->vertices.push_back(vertices[i]);
		this->vert[i] = vertices[i];
	}

	for (size_t i = 0; i < numOfIndices; i++)
	{
		this->indices.push_back(indices[i]);
		this->indi[i] = indices[i];
	}

}

Triangle::Triangle()
{
	Primitive();

	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(0.f, 1.0f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-1.0f, -1.0f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(1.f, -1.f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0, 1, 2	//Triangle 1
	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}

Quad::Quad()
{
	Primitive();
	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(-1.5, 1.0, -1.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f),//0
		glm::vec3(-1.5, -1.0, -1.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//1
		glm::vec3(1.5, -1.0, -1.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//2
		glm::vec3(1.5, 1.0, -1.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f) //3
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0,1,2,
		0,2,3
	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}


Floor::Floor()
{
	Primitive();
	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(-10.000000, 0.000000, -10.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f),//0
		glm::vec3(-10.000000, 0.000000, 10.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//1
		glm::vec3(10.000000, 0.000000, 10.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//2
		glm::vec3(10.000000, 0.000000, -10.000000),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f) //3
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0,1,2,
		0,2,3
	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}


Pyramid::Pyramid()
{
	Primitive();
	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		//Triangle front
		glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

		//Triangle left
		glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

		//Triangle back
		glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

		//Triangles right
		glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f),

		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(-.5f, -0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
		
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.0f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.0f, .0f),		glm::vec3(0.f, -1.f, 0.f),
		glm::vec3(.5f, -0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.0f, 1.f),		glm::vec3(0.f, -1.f, 0.f),


	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	this->set(vertices, numOfVertices, nullptr, 0);
}

Cube::Cube()
{
	Primitive();
	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

		glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
		glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
		glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3,

		7, 6, 1,
		7, 1, 0,

		4, 5, 6,
		4, 6, 7,

		3, 2, 5,
		3, 5, 4
	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}

Box::Box()
{
	Primitive();
	Vertex vertices[] =
	{
		//Position								//Color							//Texcoords					//Normals
		glm::vec3(-5.f, 5.f, 5.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f), //0
		glm::vec3(-5.f, -5.f, 5.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f), //1
		glm::vec3(5.f, -5.f, 5.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f), //2
		glm::vec3(5.f, 5.f, 5.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f), //3

		glm::vec3(5.f, 5.f, -5.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f), //4
		glm::vec3(5.f, -5.f, -5.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f), //5
		glm::vec3(-5.f, -5.f, -5.f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f), //6
		glm::vec3(-5.f, 5.f, -5.f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)  //7
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		3,2,1,
		3,1,0,

		0, 1, 6,
		0, 6, 7,

		7, 6, 5,
		7, 5, 4,

		4, 5, 2,
		4, 2, 3,

		0, 4, 3,
		0, 7, 4,


		5,6,1,
		5,1,2

	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}

Butt::Butt()
{
	Primitive();

	Vertex vertices[] =
	{
		glm::vec3(-.95f, .7f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f),//0
		glm::vec3(-.95f, .3f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//1
		glm::vec3(.15f, .3f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//2
		glm::vec3(.15f, .7f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f) //3
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0,1,2,
		0,2,3
	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}

Test::Test()
{
	Primitive();

	Vertex vertices[] =
	{
		glm::vec3(-.95f, .2f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f),//0
		glm::vec3(-.95f, -.2f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(0.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//1
		glm::vec3(.15f, -.2f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,0.0f), glm::vec3(0.0f,0.0f,1.0f),//2
		glm::vec3(.15f, .2f, 0.f),		glm::vec3(1.0f,1.0f,1.0f),		glm::vec2(1.0f,1.0f), glm::vec3(0.0f,0.0f,1.0f) //3
	};
	unsigned numOfVertices = sizeof(vertices) / sizeof(Vertex);

	GLuint indices[] =
	{
		0,1,2,
		0,2,3
	};
	unsigned numOfIndices = sizeof(indices) / sizeof(GLuint);

	this->set(vertices, numOfVertices, indices, numOfIndices);
}
