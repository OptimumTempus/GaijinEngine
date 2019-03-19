#include "Texture.h"



Texture::Texture(const char* fileName, GLenum type, GLint texture_unit,bool rgba)
{
	
	this->type = type;
	this->textureUnit = texture_unit;


	if (fileName != "")
	{
		unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);



		glGenTextures(1, &this->id);
		glBindTexture(GL_TEXTURE_2D, this->id);


		if (image)
		{
			if (RGBA == false)
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			}

			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "TEXTURE ERROR: LoadImage, texture loading failed! In file: " << fileName << std::endl;
		}


		/*glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, this->id);*/
		SOIL_free_image_data(image);
	}
	
}

Texture::Texture()
{
	
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}


GLuint Texture::getID() const
{
	return this->id;
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 +textureUnit);
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureUnit()
{
	return this->textureUnit;
}
