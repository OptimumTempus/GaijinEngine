#include "Object_2D.h"
#include<glm.hpp>
Object_2D::Object_2D(glm::vec3 position, std::string objectName, const char * vertexShader, const char * geometryShader, const char * fragmentShader, const char * textureRes, const char * textureSpec, GLint textNum, GLint specNum, float alpha, int objectNum)
{
	this->objectName = objectName;
	this->objectID = objectNum;

	this->shader = new Shader(vertexShader, geometryShader, fragmentShader);
	this->mesh = new Mesh(&Quad(), position, glm::vec3(0.f), glm::vec3(1.0));
	this->texture = new Texture(textureRes, GL_TEXTURE_2D, textNum, true);
	this->specularTexture = new Texture(textureSpec, GL_TEXTURE_2D, specNum, true);

	this->material = new Material(1.0,glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture->getTextureUnit(), specularTexture->getTextureUnit());

	this->shader->set1f(alpha, "alpha");
	this->shader->use();
	this->shader->set1i(texture->getTextureUnit(), "texture0");
	this->shader->set1i(specularTexture->getTextureUnit(), "texture1");
	this->material->sendToShader(*shader);
}

Object_2D::Object_2D(Primitive* Yeet, glm::vec3 position, std::string objectName, const char* vertexShader, const char* geometryShader, const char* fragmentShader, const char* textureRes, const char* textureSpec, GLint textNum, GLint specNum, float alpha, int objectNum)
{
	this->objectName = objectName;
	this->objectID = objectNum;

	this->shader = new Shader(vertexShader, geometryShader, fragmentShader);
	this->mesh = new Mesh(Yeet, position, glm::vec3(0.f), glm::vec3(1.0));
	this->texture = new Texture(textureRes, GL_TEXTURE_2D, textNum, true);
	this->specularTexture = new Texture(textureSpec, GL_TEXTURE_2D, specNum, true);

	this->material = new Material(1.0, glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture->getTextureUnit(), specularTexture->getTextureUnit());

	this->shader->set1f(alpha, "alpha");
	this->shader->use();
	this->shader->set1i(texture->getTextureUnit(), "texture0");
	this->shader->set1i(specularTexture->getTextureUnit(), "texture1");
	this->material->sendToShader(*shader);
}


void Object_2D::render(GLfloat width, GLfloat height, float alpha)
{
	glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));


	this->set(projectionMatrix, alpha);
	this->texture->bind();
	this->specularTexture->bind();

	this->shader->use();
	this->mesh->render(shader);
}

void Object_2D::set(glm::mat4 projectionMatrix, float alpha)
{
	this->shader->set1f(alpha, "alpha");
	this->shader->setMat4fv(projectionMatrix, "ProjectionMatrix", GL_FALSE);
}
