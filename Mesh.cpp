#include "Mesh.h"


bool Mesh::loadModelFromFile(std::string fileName)
{
	if (debugInfo)
		std::cout << "\nDebug:: Loading model: " << fileName << "\n" << std::endl;

	bool is_work = true;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;
	in_file.open(fileName);


	std::string subStr = "";
	std::string subSubStr = "";
	double vX = 0.0, vY = 0.0, vZ = 0.0;
	double vtX = 0.0, vtY = 0.0;
	double vnX = 0.0, vnY = 0.0, vnZ = 0.0;

	int fX = 0, fY = 0, fZ = 0;
	int fTex1 = 0, fTex2 = 0, fTex3 = 0;
	int fNorm1 = 0, fNorm2 = 0, fNorm3 = 0;



	int numVert = 0;
	int numNorm = 0;
	int numTri = 0;
	int numText = 0;
	std::string debugLog = "";

	int a = 0;
	int b = 0;

	bool isTexCoord = false;
	int traverse = 0;
	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			vX = vY = vZ = vtX = vtY = vnX = vnY = vnZ = 0.0;
			fX = fY = fZ = fTex1 = fTex2 = fTex3 = fNorm1 = fNorm2 = fNorm3 = 0;
			subStr = subSubStr = "";
			isTexCoord = true;
			

			if (temp.at(1) == 'n')
			{
				if (debugInfo)
					std::cout << "Normal: ";
				subStr = temp.substr(2, temp.length());

				std::istringstream iss(subStr);

				iss >> vnX;
				iss >> vnY;
				iss >> vnZ;

				if (debugInfo)
				{
					std::cout << vnX << " ";
					std::cout << vnY << " ";
					std::cout << vnZ << " ";

					std::cout << std::endl;
				}

				vertices[numNorm].normal = (glm::vec3(vnX, vnY, vnZ));

				numNorm++;
			}
			else if (temp.at(1) == 't' && temp.at(2) != 'l')
			{
				if (debugInfo)
					std::cout << "Texture: ";
				subStr = temp.substr(3, temp.length());

				std::istringstream iss(subStr);

				iss >> vtX;
				iss >> vtY;

				if (debugInfo)
				{
					std::cout << vtX << " ";
					std::cout << vtY << " ";

					std::cout << std::endl;
				}

				vertices[numText].texcoord = (glm::vec2(vtX, vtY));
				numText++;
			}

			else if (temp.at(0) == 'v')
			{
				if (debugInfo)
					std::cout << "Vertex: ";
				subStr = temp.substr(1, temp.length());

				std::istringstream iss(subStr);

				iss >> vX;
				iss >> vY;
				iss >> vZ;

				if (debugInfo)
				{

					std::cout << vX << " ";
					std::cout << vY << " ";
					std::cout << vZ << " ";

					std::cout << std::endl;
				}

				vertices[numVert].position = (glm::vec3(vX, vY, vZ));
				numVert++;
			}
			else if (temp.at(0) == 'f')
			{
				if (debugInfo)
					std::cout << "Face: ";
				subStr = temp.substr(2, temp.length());

				std::replace(subStr.begin(), subStr.end(), '/', ' ');

				//std::cout << subStr << std::endl;

				std::istringstream iss(subStr);

				iss >> fX;
				//iss >> fTex1;
				iss >> fNorm1;

				iss >> fY;
				//iss >> fTex2;
				iss >> fNorm2;

				iss >> fZ;
				//iss >> fTex3;
				iss >> fNorm3;

				/*std::cout << "f: " << fX << " " << fY << " " << fZ << std::endl;
				std::cout << "t: " << fTex1 << " " << fTex2 << " " << fTex3 << std::endl;
				std::cout << "n: "<< fNorm1 << " " << fNorm2 << " " << fNorm3 << std::endl;*/

				fX = fX - 1;
				indices[numTri] = fX;
				numTri++;

				fY = fY - 1;
				indices[numTri] = fY;
				numTri++;

				fZ = fZ - 1;
				indices[numTri] = fZ;
				numTri++;

			}

			//double r = ((double)rand() / (100000.0));
			//double g = ((double)rand() / (100000.0));
			//double b = ((double)rand() / (100000.0));
			double r = 1.0;
			double g = 0.0;
			double b = 0.0;

			//std::cout << r << " " << g << " " << b << std::endl;

			vertices[traverse].color = glm::vec3(r, g, b);


			traverse++;
			src += temp + "\n";
		}
		if (debugInfo)
		{
			if (!isTexCoord)
				std::cout << "No texture coordinates found in file." << std::endl;
			std::cout << "Num vert: " << numVert << " Num text: " << numText << " Num norm: " << numNorm << " Num tri: " << numTri / 3 << " " << std::endl;
			std::cout << "End Loading Model: " << fileName << "\n" << std::endl;
		}
	}
	else
	{
		std::cout << "ERROR: loadModel.cpp, could not open model file: " << fileName << "!" << std::endl;
		is_work = false;
	}
	in_file.close();


	if (debugInfo)
		std::cout << src << std::endl;


	return is_work;
}

void Mesh::initVAO(Vertex * vertexArray, const unsigned & numOfVertices, GLuint * indexArray, const unsigned & numOfIndices)
{
	this->numOfVertices = numOfVertices;
	this->numOfIndices = numOfIndices;


	 
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW


	if (this->numOfIndices > 0)
	{
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	}

	//Position
	//Gluint attribLoc = glGetAttribLocation(core_program, "vertex_position"); if want to not define in shaders
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Mesh::initVAOWithPrim(Primitive * primitive)
{
	
	this->numOfVertices = primitive->getNumOfVertices();
	this->numOfIndices = primitive->getNumOfIndices();

	for (int c = 0; c < primitive->returnVertSize(); c++)
	{
		vertices[c] = primitive->returnVerts(c);
	}

	for (int c = 0; c < primitive->returnIndiSize(); c++)
	{
		indices[c] = primitive->returnIndis(c);
	}

	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);


	glGenBuffers(1, &this->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->numOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW); //GL_DYNAMIC_DRAW

	if (this->numOfIndices > 0)
	{
		glGenBuffers(1, &this->EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);

	}
	

	//Position
	//Gluint attribLoc = glGetAttribLocation(core_program, "vertex_position"); if want to not define in shaders
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}


void Mesh::updateUniforms(Shader * shader)
{
	shader->setMat4fv(this->ModelMatrix, "ModelMatrix", GL_FALSE);
}

void Mesh::updateModelMatrix()
{
	this->ModelMatrix = glm::mat4(1.f);
	this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));
	this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));
	this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
}

Mesh::Mesh()
{
}

Mesh::Mesh(Vertex * vertexArray, const unsigned & numOfVertices, GLuint * indexArray, const unsigned & numOfIndices, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	this->initVAO(vertexArray, numOfVertices, indexArray, numOfIndices);
	this->updateModelMatrix();
}

Mesh::Mesh(Primitive* primitive, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	this->initVAOWithPrim(primitive);
	this->updateModelMatrix();
}

Mesh::Mesh(std::string fileName, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{

	debugInfo = false;

	if (!this->loadModelFromFile(fileName))
		std::cout << "MESH ERROR: LOAD FILE " << fileName << std::endl;

	numOfIndices = sizeof(indices) / sizeof(GLuint);
	numOfVertices = sizeof(vertices) / sizeof(Vertex);

	//for (int a = 0; a < numOfIndices-1; a++)
	//{
	//	std::cout << indices[a] <<  " ";

	//}

	//std::cout << "\n";

	//for (int a = 0; a < numOfVertices-1; a++)
	//{
	//std::cout << vertices[a].position.x << " " << vertices[a].position.y << " " << vertices[a].position.z << std::endl;
	//}
	//std::cout << "\n";


	this->position = position;
	this->rotation = rotation;
	this->scale = scale;


	this->initVAO(vertices, numOfVertices, indices, numOfIndices);
	this->updateModelMatrix();
}



Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	if (this->numOfIndices > 0)
	{
		glDeleteBuffers(1, &this->EBO);
	}
}

void Mesh::setPosition(const glm::vec3 position)
{
	this->position = position;
}

void Mesh::setRotation(const glm::vec3 rotation)
{
	this->rotation = rotation;
}

void Mesh::setScale(const glm::vec3 scale)
{
	this->scale = scale;
}

void Mesh::move(const glm::vec3 position)
{
	this->position += position;
}

void Mesh::move(const float & dt, const int direction)
{
	

	switch (direction)
	{
	case 0:
		this->position += glm::vec3(0.0f,0.0f,this->moveSpeed* dt);
		break;
	case 1:
		this->position -= glm::vec3(0.0f, 0.0f, this->moveSpeed* dt);
		break;
	case 2:
		this->position -= glm::vec3(this->moveSpeed * dt,0.0f,0.0f);
		break;
	case 3:
		this->position += glm::vec3(this->moveSpeed * dt, 0.0f, 0.0f);
		break;
	case 4:
		this->position += glm::vec3(0.f,this->moveSpeed * dt,0.0f);
		break;
	case 5:
		this->position -= glm::vec3(0.f, this->moveSpeed * dt, 0.0f);
		break;
	default:
		break;
	}
}

void Mesh::rotate(const glm::vec3 rotation)
{
	this->rotation += rotation;
}

void Mesh::_scale(const glm::vec3 scale)
{
	this->scale += scale;
}


void Mesh::render(Shader * shader)
{
	//Update uniforms 
	this->updateModelMatrix();
	this->updateUniforms(shader);

	shader->use();
	//Bind VAO
	glBindVertexArray(this->VAO);

	//Render
	//std::cout << "YEET" << std::endl;
	if(wireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT, GL_FILL);
	if (this->numOfIndices == 0)
		glDrawArrays(GL_TRIANGLES, 0, this->numOfVertices);
	else
		glDrawElements(GL_TRIANGLES, this->numOfIndices, GL_UNSIGNED_INT, 0);
}
