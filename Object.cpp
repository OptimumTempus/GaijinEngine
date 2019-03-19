#include "Object.h"


Object::Object(glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader,const char* textureRes, const char* textureSpec,GLint textNum, GLint specNum, BBType bbType, int objectNum)
{
	this->objectName = objectName;
	this->objectID = objectNum;

	this->shader = new Shader(vertexShader, geometryShader, fragmentShader);
	this->mesh = new Mesh(&Quad(), position, glm::vec3(0.f), glm::vec3(1.0));
	this->texture = new Texture(textureRes, GL_TEXTURE_2D, textNum, true);
	this->specularTexture = new Texture(textureSpec, GL_TEXTURE_2D, specNum, true);
	
	this->material = new Material(1.0,glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture->getTextureUnit(), specularTexture->getTextureUnit());


	this->shader->use();
	this->shader->set1i(texture->getTextureUnit(), "texture0");
	this->shader->set1i(specularTexture->getTextureUnit(), "texture1");
	this->material->sendToShader(*shader);

	this->boundingBox = new AABB(position, this->BBCheck(), bbType);

}

Object::Object(Primitive* Yeet, glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum,BBType bbType, int objectNum)
{
	this->objectName = objectName;
	this->objectID = objectNum;

	this->shader = new Shader(vertexShader, geometryShader, fragmentShader);
	this->mesh = new Mesh(Yeet, position, glm::vec3(0.f), glm::vec3(1.0));
	this->texture = new Texture(textureRes, GL_TEXTURE_2D, textNum, true);
	this->specularTexture = new Texture(textureSpec, GL_TEXTURE_2D, specNum, true);

	this->material = new Material(1.0,glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture->getTextureUnit(), specularTexture->getTextureUnit());


	this->shader->use();
	this->shader->set1i(texture->getTextureUnit(), "texture0");
	this->shader->set1i(specularTexture->getTextureUnit(), "texture1");
	this->material->sendToShader(*shader);
	

	this->boundingBox = new AABB(position, this->BBCheck(), bbType);

}

Object::Object(std::string fileName, glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum,BBType bbType, int objectNum)
{
	this->objectName = objectName;
	this->objectID = objectNum;

	this->shader = new Shader(vertexShader, geometryShader, fragmentShader);
	this->mesh = new Mesh(fileName,position, glm::vec3(0.f), glm::vec3(1.0));
	this->texture = new Texture(textureRes, GL_TEXTURE_2D, textNum, true);
	this->specularTexture = new Texture(textureSpec, GL_TEXTURE_2D, specNum, true);
	this->material = new Material(1.0,glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture->getTextureUnit(), specularTexture->getTextureUnit());


	this->shader->use();
	this->shader->set1i(texture->getTextureUnit(), "texture0");
	this->shader->set1i(specularTexture->getTextureUnit(), "texture1");
	this->material->sendToShader(*shader);

	this->boundingBox = new AABB(position, this->BBCheck(), bbType);
}

Object::Object()
{
	this->objectName = "Dab On Haters";
	this->objectID = -1;

	this->shader = new Shader();
	this->mesh = new Mesh();
	this->texture = new Texture();
	this->specularTexture = new Texture();
	this->material = new Material();


	this->shader->use();
	this->shader->set1i(texture->getTextureUnit(), "texture0");
	this->shader->set1i(specularTexture->getTextureUnit(), "texture1");
	this->material->sendToShader(*shader);
	
	this->boundingBox = new AABB();

}

Object::~Object()
{
}

void Object::move(const float & dt, const int direction)
{

	mesh->move(dt, direction);
	this->position = mesh->getPosition();
	boundingBox->changePos(this->position);
}

void Object::setPosition(glm::vec3 position)
{
	mesh->setPosition(position);
	this->position = mesh->getPosition();
}

void Object::set(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix,glm::vec3 cameraPos, glm::vec3 lightPos,glm::vec3 lightColor)
{
	this->shader->setMat4fv(modelMatrix, "ModelMatrix", GL_FALSE);
	this->shader->setMat4fv(viewMatrix, "ViewMatrix", GL_FALSE);
	this->shader->setMat4fv(projectionMatrix, "ProjectionMatrix", GL_FALSE);

	this->shader->setVec3f(lightColor, "lightColor");
	this->shader->setVec3f(lightPos, "lightPos");
	this->shader->setVec3f(cameraPos, "cameraPos");
}

void Object::render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos, glm::vec3 lightPos, glm::vec3 lightColor)
{

	this->set(modelMatrix, viewMatrix, projectionMatrix,cameraPos, lightPos, lightColor);
	this->texture->bind();
	this->specularTexture->bind();

	this->shader->use();
	this->mesh->render(shader);
}


void Light::render(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPos)
{
	this->set(modelMatrix, viewMatrix, projectionMatrix, cameraPos, this->position, this->color);
	this->texture->bind();
	this->specularTexture->bind();
	this->shader->use();
	this->mesh->render(shader);
}

void AABB::setCheckDistance(glm::vec3 chDist)
{
	this->checkDistance = chDist;
}

void AABB::changePos(glm::vec3 pos)
{
	this->position = pos;
	//std::cout << to_string(this->position) << " " << to_string(positionDirectionBig) << " "  << to_string(positionDirectionSmall)<< std::endl;
}

bool AABB::isColliding(Object otherObject)
{
	AABB* otherBoundingBox = otherObject.boundingBox;
	float distanceTo = 0.0;
	if (aabbType == Sphere && otherBoundingBox->aabbType == Sphere)
	{
		distanceTo = sqrt(pow(this->position.x - otherBoundingBox->position.x, 2.0) + pow(this->position.y - otherBoundingBox->position.y, 2.0) + pow(this->position.z - otherBoundingBox->position.z, 2.0));

		//std::cout << this->radius << " " <<otherBoundingBox->radius << std::endl;
		return distanceTo < (this->radius + otherBoundingBox->radius);
	}

	if (aabbType == Elipse && otherBoundingBox->aabbType == Sphere)
	{
		distanceTo = sqrt(pow(this->position.x - otherBoundingBox->position.x, 2.0) + pow(this->position.y - otherBoundingBox->position.y, 2.0) + pow(this->position.z - otherBoundingBox->position.z, 2.0));

		//std::cout << this->radius << " " <<otherBoundingBox->radius << std::endl;
		return (distanceTo < (this->checkDistance.x + otherBoundingBox->radius)) && (distanceTo < (this->checkDistance.y + otherBoundingBox->radius));
	}

	if (aabbType == Elipse && otherBoundingBox->aabbType == Cube)
	{
		float x = max((otherBoundingBox->smallest.x + otherBoundingBox->position.x), min(this->position.x, (otherBoundingBox->biggest.x + otherBoundingBox->position.x)));
		float y = max((otherBoundingBox->smallest.y + otherBoundingBox->position.y), min(this->position.y, (otherBoundingBox->biggest.y + otherBoundingBox->position.y)));
		float z = max((otherBoundingBox->smallest.z + otherBoundingBox->position.z), min(this->position.z, (otherBoundingBox->biggest.z + otherBoundingBox->position.z)));
		

		distanceTo = sqrt(pow(x - this->position.x, 2.0) + pow(y - this->position.y, 2.0) + pow(z - this->position.z, 2.0));


		return (distanceTo < this->checkDistance.x);
	}


	return false;
}


void Camera::updateCameraVectors()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->front = glm::normalize(this->front);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
{
	std::vector<float> vec = { 0,0,0,0,0,0 };
	this->boundingBox = new AABB(position, vec, Elipse);
	this->ViewMatrix = glm::mat4(1.f);

	this->movementSpeed = 3.f;
	this->sensitivity = 40.f;

	this->worldUp = worldUp;
	this->position = position;
	this->right = glm::vec3(0.f);
	this->up = worldUp;

	this->pitch = 0.f;
	this->yaw = -90.f;
	this->roll = 0.f;

	this->updateCameraVectors();
}

void Camera::set(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp)
{

	this->worldUp = worldUp;
	this->position = position;
	this->right = glm::vec3(0.f);
	this->up = worldUp;

	this->pitch = 0.f;
	this->yaw = -90.f;
	this->roll = 0.f;

	this->updateCameraVectors();
}

Camera::~Camera()
{
}



void Camera::setX(double num)
{
	this->position.x = num;
}

void Camera::setY(double num)
{
	this->position.y = num;
}

void Camera::setZ(double num)
{
	this->position.z = num;
}

const glm::mat4 Camera::getViewMatrix()
{
	this->updateCameraVectors();

	this->ViewMatrix = glm::lookAt(this->position, this->position + this->front, this->up);

	return this->ViewMatrix;
}

const glm::vec3 Camera::getPosition() const
{
	return this->position;
}

void Camera::move(const float & dt, const int direction)
{

	//Update position vector
	switch (direction)
	{
	case FORWARD:
		this->position += this->front * this->movementSpeed * dt;
		break;
	case BACKWARD:
		this->position -= this->front * this->movementSpeed * dt;
		break;
	case LEFT:
		this->position -= this->right * this->movementSpeed * dt;
		break;
	case RIGHT:
		this->position += this->right * this->movementSpeed * dt;
		break;
	case UP:
		this->position.y += this->movementSpeed * dt;
		break;
	case DOWN:
		this->position.y -= this->movementSpeed * dt;
		break;
	default:
		break;
	}
	this->boundingBox->changePos(this->position);
}

void Camera::move(const float & dt, const int direction, std::vector<Object> obj)
{
	bool collide = false;
	for (int c = 0; c < obj.size(); c++)
	{
		if (this->boundingBox->isColliding(obj.at(c)))
		{
			std::cout << obj.at(c).getObjectName() << " collision! Object coordinates: " << to_string(obj.at(c).getPosition()) << std::endl;
			collide = true;
		}
	}

	//Update position vector
	switch (direction)
	{
	case FORWARD:
		if (collide)
		{
			this->position -= this->front * this->movementSpeed * dt;
		}
		else
			this->position += this->front * this->movementSpeed * dt;
		break;
	case BACKWARD:
		if (collide)
		{
			this->position += this->front * this->movementSpeed * dt;

		}
		else
			this->position -= this->front * this->movementSpeed * dt;
		break;
	case LEFT:
		if (collide)
		{
			this->position += this->right * this->movementSpeed * dt;
		}
		else
			this->position -= this->right * this->movementSpeed * dt;
		break;
	case RIGHT:
		if (collide)
		{
			this->position -= this->right * this->movementSpeed * dt;
		}
		else
			this->position += this->right * this->movementSpeed * dt;
		break;
	case UP:
		if (collide)
		{
			this->position.y -= this->movementSpeed * dt;
		}
		else
			this->position.y += this->movementSpeed * dt;
		break;
	case DOWN:
		if (collide)
		{
			this->position.y += this->movementSpeed * dt;
		}
		else
			this->position.y -= this->movementSpeed * dt;
		break;
	default:
		break;
	}
	this->boundingBox->changePos(this->position);
}

void Camera::updateMouseInput(const float & dt, const double & offsetX, const double & offsetY, bool inverted)
{
	if (inverted != true)
	{
		this->pitch += static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;
	}
	else
	{
		this->pitch -= static_cast<GLfloat>(offsetY) * this->sensitivity * dt;
		this->yaw += static_cast<GLfloat>(offsetX) * this->sensitivity * dt;
	}


	if (this->pitch > 80.f)
		this->pitch = 80.f;
	else if (this->pitch < -80.f)
		this->pitch = -80.f;

	if (this->yaw > 360.f || this->yaw < -360.f)
		this->yaw = 0.f;
}

void Camera::updateInput(const float & dt, const int direction, const double & offsetX, const double & offsetY)
{
	this->updateMouseInput(dt, offsetX, offsetY, false);
}

const float Camera::getPitch() const
{
	return pitch;
}

const float Camera::getYaw() const
{
	return yaw;
}

const float Camera::getRoll() const
{
	return roll;
}

glm::vec3 Camera::getFront()
{
	return front;
}
