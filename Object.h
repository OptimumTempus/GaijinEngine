#ifndef OBJECT_H
#define OBJECT_H
#pragma once

#include"Include/glm_libs.h"
#include<string>
#include<iostream>
#include<tuple>
#include<math.h>
#include<vector>

class Camera;
class Object;
class AABB;



enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT, UP, DOWN };

static const float GH_GRAVITY = -9.8f;
static const float GH_WALK_SPEED = 2.9f;
static const float GH_WALK_ACCEL = 50.0f;



enum MapSection
{
	FUL = 0,
	FUR,
	BUL,
	BUR,
	FLL,
	FLR,
	BLL,
	BLR
};

enum BBType
{
	Sphere = 0,
	Cube,
	Plane,
	Elipse
};


class Object
{

public:
	Object(glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum, BBType bbType, int objectNum);
	Object(Primitive* Yeet, glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum, BBType bbType, int objectNum);
	Object(std::string fileName, glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum, BBType bbType, int objectNum);
	Object();

	~Object();

	void move(const float & dt, const int direction);


	void setPosition(glm::vec3 position);


	inline void rotate(glm::vec3 rotate)
	{
		mesh->rotate(rotate);
	};

	inline void setRotation(glm::vec3 rotate)
	{
		mesh->setRotation(rotate);
	};

	inline glm::vec3 getPosition()
	{
		return mesh->getPosition();
	};


	void set(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos, glm::vec3 lightPos, glm::vec3 lightColor);
	void render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos, glm::vec3 lightPos, glm::vec3 lightColor);

	inline std::string getObjectName()
	{
		return this->objectName;
	};

	inline void toggleWireFrame()
	{
		mesh->toggleWireFrame();
	}

	/*inline bool isCollide(Object& otherObject)
	{
		isClipped = false;
		std::cout << this->objectName << ": " << to_string(this->position) << std::endl;
		std::cout << otherObject.objectName << ": " << to_string(otherObject.position) << std::endl;

		float distanceTo = sqrt(pow(this->position.x - otherObject.position.x, 2.0) + pow(this->position.y - otherObject.position.y, 2.0) + pow(this->position.z - otherObject.position.z, 2.0));

		std::cout << distanceTo << "\n" << std::endl;

		if (distanceTo <= 1.0)
			isClipped = true;

		return isClipped;
	};*/

	inline std::vector<float> BBCheck()
	{
		float biggestX;
		float biggestY;
		float biggestZ;

		float smallestX;
		float smallestY;
		float smallestZ;

		float tempX;
		float tempY;
		float tempZ;

		std::cout << this->objectName << std::endl;
		for (int c = 0; c < (sizeof(mesh->vertices) / sizeof(*mesh->vertices)); c++)
		{	
			//std::cout << to_string(mesh->vertices[c].position) << std::endl;
			
			if (c == 0)
			{
				biggestX = mesh->vertices[c].position.x;
				biggestY = mesh->vertices[c].position.y;
				biggestZ = mesh->vertices[c].position.z;

				smallestX = mesh->vertices[c].position.x;
				smallestY = mesh->vertices[c].position.y;
				smallestZ = mesh->vertices[c].position.z;
			}
			else
			{
				tempX = mesh->vertices[c].position.x;
				tempY = mesh->vertices[c].position.y;
				tempZ = mesh->vertices[c].position.z;

				if (tempX > biggestX)
					biggestX = tempX;

				if (tempX < smallestX)
					smallestX = tempX;

				if (tempY > biggestY)
					biggestY = tempY;

				if (tempY < smallestY)
					smallestY = tempY;

				if (tempZ > biggestZ)
					biggestZ = tempZ;

				if (tempZ < smallestZ)
					smallestZ = tempZ;
			}
		}

		return std::vector<float> {biggestX, biggestY, biggestZ, smallestX, smallestY, smallestZ};
	};

	AABB* boundingBox;

protected:
	bool isClipped;
	glm::vec3 position;
	std::string objectName;
	int objectID;
	Shader* shader;
	Mesh* mesh;
	Texture* texture;
	Texture* specularTexture;
	Material* material;

};

class Light : public Object
{
public:
	Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation) : Object("Models/TestSphere.obj", position, "Light", "Shaders/glowVertex.glsl", "", "Shaders/glowFragment.glsl", "", "", 0, 1,Sphere, 0)
	{
		this->position = position;
		this->color = color;
		this->attenuation = attenuation;
		mesh->setScale(glm::vec3(1.f, 1.f, 1.f));
		mesh->setPosition(this->position);
	};

	inline void setAttenuation(glm::vec3 attenuation)
	{
	};

	inline glm::vec3 getAttenuation()
	{
		return this->attenuation;
	};



	inline glm::vec3 getColor()
	{
		return this->color;
	}

	inline void setColor(glm::vec3 color)
	{
		this->color = color;
	}

	void render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos);

private:
	glm::vec3 color;
	glm::vec3 attenuation = glm::vec3(1.0f, .0f, .0f);
};

class Camera
{


private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;

	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	void updateCameraVectors();

	glm::vec2 collisionElipse;


public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);

	~Camera();
	glm::vec3 position;

	void setX(double num);
	void setY(double num);
	void setZ(double num);
	const glm::mat4 getViewMatrix();
	const glm::vec3 getPosition() const;
	void set(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp);
	void move(const float& dt, const int direction);
	void move(const float& dt, const int direction, std::vector<Object> obj);

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY, bool inverted);
	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY);
	const float getPitch() const;
	const float getYaw() const;
	const float getRoll() const;
	glm::vec3 getFront();

	AABB* boundingBox;
};

class AABB
{

public:
	AABB()
	{
		position = glm::vec3(0.0f);
		checkDistance = glm::vec3(0.0f);
		radius = 0.0;
		aabbType = Elipse;
	};
	AABB(glm::vec3 position, std::vector<float> vec, BBType type)
	{
		this->position = position;
		aabbType = type;
		biggest = glm::vec3(vec.at(0), vec.at(1), vec.at(2));
		smallest = glm::vec3(vec.at(3), vec.at(4), vec.at(5));

		float distanceTo = sqrt(pow(biggest.x - smallest.x, 2.0) + pow(biggest.y - smallest.y, 2.0) + pow(biggest.z - smallest.z, 2.0));
		std::cout << "Biggest Values " << "X: " << biggest.x << " Y: " << biggest.y << " Z: " << biggest.z << std::endl;
		std::cout << "Smallest Values " << "X: " << smallest.x << " Y: " << smallest.y << " Z: " << smallest.z << std::endl;

		glm::vec3 planeDistance(0.0f);
		if (biggest.x == 0 && smallest.x == 0)
		{
			planeDistance = glm::vec3(0, distanceTo / sqrt(2), distanceTo / sqrt(2));
		}

		if (biggest.y == 0 && smallest.y == 0)
		{
			planeDistance = glm::vec3(distanceTo / sqrt(2), 0, distanceTo / sqrt(2));
		}

		if (biggest.z == 0 && smallest.z == 0)
		{
			planeDistance = glm::vec3(distanceTo / sqrt(2), distanceTo / sqrt(2), 0);
		}



		switch (aabbType)
		{
		case Sphere:
		{
			std::cout << "Sphere Radius: " << (distanceTo/sqrt(3.0)) /2.0<< std::endl;
			radius = (distanceTo / sqrt(3.0)) / 2.0;
		}break;
		case Cube:
		{
			radius = (distanceTo / sqrt(3))/2;
			std::cout << "Cube Side Length: " << (distanceTo / sqrt(3))/2 << std::endl;
			checkDistance = glm::vec3(distanceTo/sqrt(3));
		}break;
		case Plane:
		{
			std::cout << "Square Side Length: " << (distanceTo / sqrt(2))/2 << std::endl;
			checkDistance = planeDistance;
		}break;
		case Elipse:
		{
			checkDistance = glm::vec3(.35, .10, .10);
			radius = .75;
		}break;
		default:
		{
			checkDistance = glm::vec3(0);
			radius = 0.0;
		}
			break;
		}

	};

	~AABB()
	{

	};


	void setCheckDistance(glm::vec3 chDist);

	void changePos(glm::vec3 pos);

	bool isColliding(Object otherObject);

	glm::vec3 biggest;
	glm::vec3 smallest;
	glm::vec3 positionDirectionBig;
	glm::vec3 positionDirectionSmall;




	glm::vec3 position;
	glm::vec3 checkDistance;
	float radius;
	BBType aabbType;
protected:
	//glm::vec3 biggest;
	//glm::vec3 smallest;
	//glm::vec3 positionDirectionBig;
	//glm::vec3 positionDirectionSmall;




	//glm::vec3 position;
	//glm::vec3 checkDistance;
	//float radius;
	//BBType aabbType;

private:

};
#endif