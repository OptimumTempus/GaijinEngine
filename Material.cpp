#include "Material.h"

Material::Material(float attenuation, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLint diffuseTex, GLint specularTex)
{
	this->attenuation = attenuation;
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->diffuseTex = diffuseTex;
	this->specularTex = specularTex;
}

Material::Material()
{

}

Material::~Material()
{
	
}

void Material::sendToShader(Shader& program)
{

	program.set1f(this->attenuation, "material.attenuation");
	program.setVec3f(this->ambient, "material.ambient");
	program.setVec3f(this->diffuse, "material.diffuse");
	program.setVec3f(this->specular, "material.specular");

	program.set1i(this->diffuseTex, "material.diffuseTex");
	program.set1i(this->specularTex, "material.specularTex");

}
