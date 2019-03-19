#include <iostream>
#include <map>
#include <string>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// GLM
#include <glm.hpp>
#include<mat4x2.hpp>
#include<mat4x3.hpp>
#include<mat4x4.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h> 
#include FT_FREETYPE_H
// GL includes
#include"Shader_s.h"

class Text
{
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

public:
	std::map<GLchar, Character> Characters;
	GLuint VAO, VBO;
	glm::mat4 projection;

	TextShader* shader;
	//TextShader shader("Shaders/text.vs", "Shaders/text.frag");
	Text(int width, int height,const char* fileName);

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color,int width, int height);
	void changeProjection(int width, int height);
private:


};