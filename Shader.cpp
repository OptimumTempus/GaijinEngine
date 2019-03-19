#include "Shader.h"



	std::string Shader::loadShaderSource(const char * fileName)
	{
		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		in_file.open(fileName);

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";

		}
		else
		{
			std::cout << "SHADER ERROR: could not open file: " << fileName << "\n";
		}

		return src;
	}

	GLuint Shader::loadShader(GLenum type,const char * fileName)
	{
		char infoLog[512];
		GLint success = 0;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName).c_str();
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "SHADER ERROR: could not compile : " << type << " shader." << std::endl;
			std::cout << infoLog << std::endl;
		}

		return shader;
	}

	void Shader::linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success = 0;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);

		if (geometryShader)
			glAttachShader(this->id, geometryShader);
		glAttachShader(this->id, fragmentShader);

		glLinkProgram(this->id);
		glUseProgram(this->id);
		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "SHADER ERROR: problem with linking!" << std::endl;
			std::cout << infoLog << std::endl;

		}

		glUseProgram(0);

	}

	Shader::Shader()
	{
	}

	Shader::Shader(const char* vertexFile, const char* geometryFile, const char* fragmentFile)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;
		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
		if(geometryFile !="")
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);

		this->linkProgram(vertexShader, geometryShader, fragmentShader);


		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(this->id);
	}

	void Shader::use()
	{
		glUseProgram(this->id);
	}

	void Shader::unuse()
	{
		glUseProgram(0);
	}

	void Shader::set1i(GLint value, const GLchar * name)
	{
		this->use();
		glUniform1i(glGetUniformLocation(this->id, name), value);
		this->unuse();
	}




	void Shader::set1f(GLfloat value, const GLchar * name)
	{
		this->use();
		glUniform1f(glGetUniformLocation(this->id, name), value);
		this->unuse();
	}

	void Shader::setVec2f(glm::fvec2 value, const GLchar * name)
	{
		this->use();
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void Shader::setVec3f(glm::fvec3 value, const GLchar* name)
	{
		this->use();
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();

	}

	void Shader::setVec4f(glm::fvec4 value, const GLchar * name)
	{
		this->use();
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
		this->unuse();
	}

	void Shader::setMat3fv(glm::mat3 value, const GLchar * name, GLboolean transpose)
	{
		this->use();
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
		this->unuse();
	}

	void Shader::setMat4fv(glm::mat4 value, const GLchar * name, GLboolean transpose)
	{
		this->use();
		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
		this->unuse();
	}

	/*bool Shader::loadShaders(GLuint & program)
	{
		bool is_work = true;
		char infoLog[512];
		GLint success = 0;

		std::string temp = "";
		std::string src = "";

		std::ifstream in_file;

		in_file.open("Shaders/vertex.glsl");

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "ERROR: load.cpp, could not open vertex file!" << std::endl;
			is_work = false;
		}
		in_file.close();


		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* vertSrc = src.c_str();
		glShaderSource(vertexShader, 1, &vertSrc, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR: load.cpp, could not compile vertex shader!" << std::endl;
			std::cout << infoLog << std::endl;
			is_work = false;

		}


		temp = "";
		src = "";

		in_file.open("Shaders/fragment.glsl");

		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
				src += temp + "\n";
		}
		else
		{
			std::cout << "ERROR: load.cpp, could not open fragment file!" << std::endl;
			is_work = false;
		}
		in_file.close();


		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragSrc = src.c_str();
		glShaderSource(fragmentShader, 1, &fragSrc, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR: load.cpp, could not compile fragment shader!" << std::endl;
			std::cout << infoLog << std::endl;
			is_work = false;

		}


		program = glCreateProgram();

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		
		glLinkProgram(program);

		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(program, 512, NULL, infoLog);
			std::cout << "ERROR: load.cpp, could not link program!" << std::endl;
			std::cout << infoLog << std::endl;
			is_work = false;

		}


		glUseProgram(0);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);


		return is_work;
	}*/
