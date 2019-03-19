#include"loadimage.h"


namespace Utils
{
	LoadTexture::LoadTexture(const char* filename)
	{
		int image_width = 0;
		int image_height = 0;

		unsigned char* image = SOIL_load_image(filename, &image_width, &image_height, NULL, SOIL_LOAD_RGBA);


		
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);



		if (image)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Error: LoadImage, texture loading failed!" << std::endl;
		}


		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, 0);
		SOIL_free_image_data(image);
	}
	GLuint LoadTexture::getTex()
	{
		return tex;
	}
}