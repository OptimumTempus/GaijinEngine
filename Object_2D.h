#include"Include/glm_libs.h"
#include<string>
#include<iostream>

class Object_2D
{
public:
	Object_2D(glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum, float alpha, int objectNum);
	Object_2D(Primitive* Yeet, glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum, float alpha, int objectNum);


	inline void move(glm::vec3 position)
	{
		mesh->move(position);
	};

	inline void setPosition(glm::vec3 position)
	{
		mesh->setPosition(position);
	};

	void render(GLfloat width, GLfloat height, float alpha);

	inline std::string getObjectName()
	{
		return this->objectName;
	};


	void set(glm::mat4 projectionMatrix, float alpha);


protected:

	glm::vec3 position;
	std::string objectName;
	int objectID;
	Shader* shader;
	Mesh* mesh;
	Texture* texture;
	Texture* specularTexture;
	Material* material;
};

class Button : public Object_2D
{
public:
	Button(Primitive* model, const char* imageName, glm::vec3 position, std::string objectName, GLint textNum, GLint specNum, float alpha, int objectNum) : Object_2D(model, position, objectName, "Shaders/2DVertex.glsl", "", "Shaders/2DFragment.glsl", imageName, "", textNum, specNum, alpha, objectNum)
	{

	};

	inline glm::vec3 getPosition()
	{
		return this->mesh->getPosition();
	};

private:
	bool isPressed;
};