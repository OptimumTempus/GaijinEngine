#include "loadModel.h"



namespace Utils
{
	LoadModel::LoadModel(std::string fileName)
	{
		debugInfo = false;

		loadModelFromFile(fileName);

		//Vertex vertices[] =
		//{
		//glm::vec3(1.000000, -1.000000, -1.000000),		glm::vec3(1.0f,0.0f,0.0f),		glm::vec2(0.0f,1.0f), //0
		//glm::vec3(1.000000, -1.000000, 1.000000),		glm::vec3(0.0f,1.0f,0.0f),		glm::vec2(0.0f,0.0f), //1

		//glm::vec3(-1.000000, -1.000000, 1.000000),		glm::vec3(0.0f,0.0f,1.0f),		glm::vec2(1.0f,0.0f), //2

		//glm::vec3(-1.000000, -1.000000, -1.000000),		glm::vec3(0.0f,1.0f,0.0f),		glm::vec2(1.0f,1.0f),  //3

		//glm::vec3(1.000000, 1.000000, -0.999999),		glm::vec3(0.0f,1.0f,0.0f),		glm::vec2(1.0f,1.0f), //4
		//glm::vec3(0.999999, 1.000000, 1.000001),		glm::vec3(0.0f,1.0f,0.0f),		glm::vec2(1.0f,.0f),  //5
		//glm::vec3(-1.000000, 1.000000, 1.000000),		glm::vec3(0.0f,1.0f,0.0f),		glm::vec2(.0f,.0f),  //6
		//glm::vec3(-1.000000, 1.000000, -1.000000),		glm::vec3(0.0f,1.0f,0.0f),		glm::vec2(.0f,1.0f) //7

		//};

		//GLuint indices[] =
		//{
		//1,3,0,
		//7,5,4,
		//4,1,0,
		//5,2,1,
		//

		//2,7,3,
		//0,7,4,
		//1,2,3,
		//7,6,5,

		//4,5,1,
		//5,6,2,
		//2,6,7,
		//0,3,7

		//};



		//for (int a = 0; a < 4; a++)
		//{
		//	std::cout << indices[a] <<  " ";

		//}

		/*std::cout << indices[0] << " " << indices[1] << " "  << indices[2]  << std::endl;*/


		/*for (int a = 0; a < 3; a++)
		{
		std::cout << vertices[a].position.x << " " << vertices[a].position.y << " " << vertices[a].position.z << std::endl;
		}
		std::cout << "\n";*/

		numOfIndices = sizeof(indices) / sizeof(GLuint);
		numOfVertices = sizeof(vertices) / sizeof(Vertex);


		VAO = NULL;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		GLuint VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) , &vertices, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);


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
		//glBindVertexArray()

		// GLuint VAO;
		//glGenVertexArrays(1, &VAO);
		//glBindVertexArray(VAO);

		//GLuint VBO;
		//glGenBuffers(1, &VBO);
		//glBindBuffer(GL_ARRAY_BUFFER, VBO);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW

		//GLuint EBO;
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		////Position
		////Gluint attribLoc = glGetAttribLocation(core_program, "vertex_position"); if want to not define in shaders
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		//glEnableVertexAttribArray(0);

		////Color
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		//glEnableVertexAttribArray(1);

		////Texture
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		//glEnableVertexAttribArray(2);

		//glBindVertexArray(0);
	}
	unsigned LoadModel::returnIndices()
	{
		return numOfIndices;
	}
	unsigned LoadModel::returnVertices()
	{
		return numOfVertices;
	}
	GLuint LoadModel::getVAO()
	{
		return VAO;
	}
	void LoadModel::bindVertexArray()
	{
		glBindVertexArray(VAO);
	}
	bool LoadModel::loadModelFromFile(std::string fileName)
	{
		toggleDebugInfo();
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
					iss >> fTex1;
					iss >> fNorm1;

					iss >> fY;
					iss >> fTex2;
					iss >> fNorm2;

					iss >> fZ;
					iss >> fTex3;
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
				std::cout << "Num vert: " << numVert << " Num text: " << numText << " Num norm: " << numNorm << " Num tri: " << numTri/3 << " " << std::endl;
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
	void LoadModel::toggleDebugInfo()
	{
		if (debugInfo == true)
			debugInfo = false;
		else if (debugInfo == false)
			debugInfo = true;
	}
}