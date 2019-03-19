#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include"Include/glm_libs.h"

#include"Object.h"
#include"Object_2D.h"
#include"Graphics/window.h"
#include <iostream>
#include<string>

#include"2D/Header.h"
//#include"Camera.h"

//Deletes CMD 
//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")


bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}


bool loadShaders(GLuint &program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	in_file.open("Shaders/2DVertex.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::LOADSHADERS::COUT_NOT_OPEN_VERTEX_FILE" << std::endl;;
		loadSuccess = false;
	}

	in_file.close();


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) 
	{
		loadSuccess = false;
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COUT_NOT_COMPILE_VERTEX_FILE" << std::endl;
		std::cout << infoLog << std::endl;
	}

	temp = "";
	src = "";

	in_file.open("Shaders/2DFragment.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
			src += temp + "\n";
	}
	else
	{
		std::cout << "ERROR::LOADSHADERS::COUT_NOT_OPEN_FRAGMENT_FILE" << std::endl;
		loadSuccess = false;
	}

	in_file.close();


	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		loadSuccess = false;
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COUT_NOT_COMPILE_FRAGMENT_FILE" << std::endl;
		std::cout << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		loadSuccess = false;
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COUND_NOT_COMPILE_PROGRAM" << std::endl;
		std::cout << infoLog << std::endl;
	}

	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
};


std::vector<Object> obj;

int main(int argc, char* args[])
{
	
	Window window("Hello World", 800, 600);
	int framebufferWidth = 0;
	int framebufferHeight = 0;
	glfwGetFramebufferSize(window.getWindow(), &framebufferWidth, &framebufferHeight);


	Text txt(framebufferWidth, framebufferHeight, "Fonts/arial.ttf");

	Utils::Timer timer;


	Light Dab(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, .0f, .0f));
	//Button button1(&Butt(), "Resources/Button1.png", glm::vec3(0.f, 0.f, 0.f), "YEET", 111, 112, 1.f, 34);
	

	

	Camera camera(glm::vec3(0.f,0.f,1.f),glm::vec3(0.f,0.f,1.f), glm::vec3(0.f, 1.f, 0.f));

	Object butthole(&Pyramid(), glm::vec3(0.0f, 0.0f, 0.0f), "Pyramid 1", "Shaders/vertex.glsl", "", "Shaders/fragment.glsl", "Resources/container.png", "Resources/container_specular.png", 2, 3,Cube, 1);
	Object rigger(&Pyramid(), glm::vec3(1.0f, 1.0f, 1.0f), "Pyramid 2", "Shaders/vertex.glsl", "", "Shaders/fragment.glsl", "Resources/container.png", "Resources/container_specular.png", 4, 5,Cube, 2);

	Object floor(&Floor(), glm::vec3(0.0f,-.5f,0.0f),"Floor", "Shaders/vertex.glsl", "", "Shaders/fragment.glsl", "Resources/container.png", "Resources/container_specular.png", 6,7,Plane, 3);


	obj.push_back(butthole);
	obj.push_back(rigger);
	obj.push_back(Dab);


	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.f));


	//Perspective
	glfwGetFramebufferSize(window.getWindow(), &framebufferWidth, &framebufferHeight);

	std::cout << "FW: " << framebufferWidth << " FH: " << framebufferHeight << std::endl;


	glm::mat4 ViewMatrix(1.f);

	float fov = 90.f;
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	glm::mat4 ProjectionMatrix(1.f);

	double lastMouseX = 0.0;
	double lastMouseY = 0.0;
	double mouseX = 0.0;
	double mouseY = 0.0;
	double mouseOffsetX = 0.0;
	double mouseOffsetY = 0.0;
	bool firstMouse = true;

	std::string yeet = "FPS: ";

	bool rer = true;
	int frame = 0;
	int yeet2 = 0;
	window.toggleMouse();
	
	//for (int c = 0; c < objectVector->size()-1; c++)
	//{

	//}

	while (!window.w_closed())
	{
		window.clear(.0f, .0f, .0f, 1.0f);
		
		timer.updateDT();
  		

			if (window.w_isKeyPressed(GLFW_KEY_ESCAPE))
			{
				break;
			}


			if (window.w_isKeyPressed(GLFW_KEY_E))
			{
				camera.set(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
				window.turnKeyPressOff(GLFW_KEY_E);
			}

			if (window.w_isKeyPressed(GLFW_KEY_M))
			{
				window.toggleMouse();
				window.turnKeyPressOff(GLFW_KEY_M);
			}

			if (window.w_isKeyPressed(GLFW_KEY_SPACE))
			{
				camera.move(timer.returnDT(), 4, obj);
			}

			if (window.w_isKeyPressed(GLFW_KEY_LEFT_CONTROL))
			{
				if (camera.getPosition().y <= 0.0f)
				{

				}
				else
					camera.move(timer.returnDT(), 5,obj);

			}

			if (window.w_isKeyPressed(GLFW_KEY_W))
			{
				camera.move(timer.returnDT(), 0, obj);

			}

			if (window.w_isKeyPressed(GLFW_KEY_S))
			{
				camera.move(timer.returnDT(), 1, obj);

			}

			if (window.w_isKeyPressed(GLFW_KEY_A))
			{
				camera.move(timer.returnDT(), 2, obj);

			}
			if (window.w_isKeyPressed(GLFW_KEY_D))
			{
				camera.move(timer.returnDT(), 3,obj);
			}


			if (window.w_isKeyPressed(GLFW_KEY_LEFT))
			{
				Dab.move(timer.returnDT(), 2);
				//window.turnKeyPressOff(GLFW_KEY_LEFT);

			}
			
			if (window.w_isKeyPressed(GLFW_KEY_RIGHT))
			{
				Dab.move(timer.returnDT(), 3);
				//window.turnKeyPressOff(GLFW_KEY_RIGHT);
			}

			if (window.w_isKeyPressed(GLFW_KEY_UP))
			{
				Dab.move(timer.returnDT(), 4);
				//window.turnKeyPressOff(GLFW_KEY_UP);

			}

			if (window.w_isKeyPressed(GLFW_KEY_DOWN))
			{
				Dab.move(timer.returnDT(), 5);
				//window.turnKeyPressOff(GLFW_KEY_DOWN);
			}

			if (window.w_isKeyPressed(GLFW_KEY_SLASH))
			{
				Dab.move(timer.returnDT(), 0);
				//window.turnKeyPressOff(GLFW_KEY_SLASH);

			}

			if (window.w_isKeyPressed(GLFW_KEY_PERIOD))
			{
				Dab.move(timer.returnDT(), 1);
				//window.turnKeyPressOff(GLFW_KEY_PERIOD);
			}

			if (window.w_isKeyPressed(GLFW_KEY_C))
			{
				butthole.move(timer.returnDT(), 1);
			}

			
			//if (Dab.boundingBox->isColliding(butthole))
			//{
			//	std::cout << "Is Colliding" << std::endl;
			//}

			//camera.boundingBox->isColliding(floor)




			glfwGetFramebufferSize(window.getWindow(), &framebufferWidth, &framebufferHeight);
			ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight), nearPlane, farPlane);

			window.w_getMousePosition(mouseX, mouseY);
			if (firstMouse)
			{
				lastMouseX = mouseX;
				lastMouseY = mouseY;
				firstMouse = false;

			}
			mouseOffsetX = mouseX - lastMouseX;
			mouseOffsetY = lastMouseY - mouseY;


			lastMouseX = mouseX;
			lastMouseY = mouseY;
			
			camera.updateMouseInput(timer.returnDT(), mouseOffsetX, mouseOffsetY, false);


			ViewMatrix = camera.getViewMatrix();

			float xl = (2.0f *  mouseOffsetX) / framebufferWidth;
			float yl = (2.0f *  mouseOffsetY) / framebufferHeight;
			float zl = 1.0f;
			glm::vec3 ray_nds = glm::vec3(xl, yl, zl);
			glm::vec4 ray_clip = glm::vec4(ray_nds.xy, -1.0, 1.0);

			//std::cout << to_string(ray_nds) << " ";

			

			ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight), nearPlane, farPlane);

			glm::vec4 ray_eye = glm::inverse(ProjectionMatrix) * ray_clip;
			ray_eye = glm::vec4(ray_eye.xy, -1.0, 0.0);

			//std::cout << to_string(ray_eye) <<  " ";


			glm::vec3 ray_wor = (glm::inverse(ViewMatrix) * ray_eye).xyz;
			// don't forget to normalise the vector at some point
			ray_wor = glm::normalize(ray_wor);
			//std::cout << to_string(ray_wor) << std::endl;
			bool yeets = true;
			float t0, t1;
			glm::vec3 orig = camera.getPosition();
			glm::vec3 center = Dab.boundingBox->position;

			glm::vec3 L = center - orig;

			float tca = glm::dot(L, ray_wor);

			float d2 = glm::dot(L, L) - tca * tca;

			std::cout << d2 << std::endl;
			if (d2 > pow(Dab.boundingBox->radius, 2.0))
				yeets = false;


			glm::vec3 L2 = orig - center;
			float a = glm::dot(ray_wor, ray_wor);
			float b = 2 * glm::dot(ray_wor, L2);
			float c = glm::dot(L2, L2) - pow(Dab.boundingBox->radius, 2.0);

			if (!solveQuadratic(a, b, c, t0, t1))
				yeets = false;


			if (t0 > t1) std::swap(t0, t1);

			if (t0 < 0) {
				t0 = t1; // if t0 is negative, let's use t1 instead 
				if (t0 < 0)
					std::cout << "Negative" << std::endl; // both t0 and t1 are negative 
			}

			//t = t0;

			if (yeets)
				Dab.setColor(glm::vec3(1.0f, 0.f, 0.f));
			else
				Dab.setColor(glm::vec3(1.f, 1.f, 1.f));


			butthole.render(ModelMatrix, ViewMatrix, ProjectionMatrix, camera.getPosition(), Dab.getPosition(), Dab.getColor());
			rigger.render(ModelMatrix, ViewMatrix, ProjectionMatrix, camera.getPosition(), Dab.getPosition(), Dab.getColor());
			Dab.render(ModelMatrix, ViewMatrix, ProjectionMatrix, camera.getPosition());
			floor.render(ModelMatrix, ViewMatrix, ProjectionMatrix, camera.getPosition(), Dab.getPosition(), Dab.getColor());

			txt.RenderText("Width: " + std::to_string(framebufferWidth), 0.0f, 50, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);
			txt.RenderText("Height: " + std::to_string(framebufferHeight), 0.0f, 25, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);


			txt.RenderText("X position: " + std::to_string(camera.getPosition().x), framebufferWidth * .5, 100, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);
			txt.RenderText("Y position: " + std::to_string(camera.getPosition().y), framebufferWidth * .5, 75, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);
			txt.RenderText("Z position: " + std::to_string(camera.getPosition().z), framebufferWidth * .5, 50, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);

			txt.RenderText("Roll: " + std::to_string(camera.getRoll()), framebufferWidth * .5, 175, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);
			txt.RenderText("Pitch: " + std::to_string(camera.getPitch()), framebufferWidth * .5, 150, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);
			txt.RenderText("Yaw: " + std::to_string(camera.getYaw()), framebufferWidth * .5, 125, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);

			txt.RenderText("+", framebufferWidth *.5, framebufferHeight*.5, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);



		yeet = "FPS: ";
		timer.runFPSCounter(&frame);
		yeet += std::to_string(frame);
		txt.RenderText(yeet, 0.0f, framebufferHeight-35, .5f, glm::vec3(1.0, 1.0f, 1.0f), framebufferWidth, framebufferHeight);

		window.w_update(); 

	}


	//glDeleteProgram(core_program);
	glfwTerminate();
	SDL_Quit();

	return 0;
}


