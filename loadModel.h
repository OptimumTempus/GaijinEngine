#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm.hpp"
#include <vector>

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<random>

namespace Utils
{

	class LoadModel
	{
		struct Vertex
		{
			glm::vec3 position;
			glm::vec3 color;
			glm::vec2 texcoord;
			glm::vec3 normal;
		};

	public:
		LoadModel(std::string fileName);


		unsigned returnIndices();
		unsigned returnVertices();
		GLuint getVAO();
		void bindVertexArray();

		bool loadModelFromFile(std::string fileName);

		void toggleDebugInfo();

	private:
		Vertex vertices[16384];
		GLuint indices[16384];
		unsigned numOfIndices;
		unsigned numOfVertices;
		GLuint VAO;
		bool debugInfo;
	};
}