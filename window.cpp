#include "window.h"

void window_Resize(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
void cursor_poistion_callback(GLFWwindow* window, double xpos, double ypos);


Window::Window(const char * wName, int width, int height)
{
	
	w_pr_WindowName = wName;
	w_pr_Width = width;
	w_pr_Height = height;


	if (!w_pr_Init())
	{
		glfwTerminate();
	}

	KeyPress temp;
	temp.isPressed = false;


	for (int i = 0; i < MAX_KEYS; i++)
	{
		w_i_pr_Keys[i] = temp;
	}

	for (int i = 0; i < MAX_MOUSEKEYS; i++)
	{
		w_i_pr_Keys[i] = temp;
	}
	hideMouse = true;
	//glfwSetInputMode(w_pr_Window, GLFW_STICKY_KEYS, GL_FALSE);
	glfwSetInputMode(w_pr_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


}

Window::~Window()
{
	glfwTerminate();
}

void Window::w_update()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cout << "WINDOW: OpenGL Error: " << error << std::endl;
	}

	glfwPollEvents();

	//glfwGetFramebufferSize(w_pr_Window, &w_pr_Width, &w_pr_Height);
	glfwSwapBuffers(w_pr_Window);
}

bool Window::w_closed() const
{
	return glfwWindowShouldClose(w_pr_Window) == 1;
}

void Window::clear(float r, float g, float b, float a) const
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

int Window::w_getWidth() const
{
	return w_pr_Width;
}

int Window::w_getHeight() const
{
	return w_pr_Height;
}

void Window::turnKeyPressOff(unsigned int key)
{
	w_i_pr_Keys[key].isPressed = false;
}

void Window::turnkeyPressOn(unsigned int key)
{
	w_i_pr_Keys[key].isPressed = true;
}

void Window::turnMousePressOff(unsigned int key)
{
	w_i_pr_MouseButtonKeys[key].isPressed = false;
}

void Window::turnMousePressOn(unsigned int key)
{
	w_i_pr_MouseButtonKeys[key].isPressed = true;
}

bool Window::w_isKeyPressed(unsigned int key)
{
	if (key >= MAX_KEYS)
		return false;

	return w_i_pr_Keys[key].isPressed;
}


bool Window::w_isMouseButtonPressed(unsigned int buttoncode) const
{
	if (buttoncode >= MAX_MOUSEKEYS)
		return false;
	return w_i_pr_MouseButtonKeys[buttoncode].isPressed;
}

void Window::w_getMousePosition(double & x, double & y) const
{
	x = w_i_pr_MouseX;
	y = w_i_pr_MouseY;

}

GLFWwindow* Window::getWindow()
{
	return w_pr_Window;
}

void Window::toggleMouse()
{
	hideMouse = !hideMouse;
	if (hideMouse)
	{
		glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
		glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}


bool Window::w_pr_Init()
{
	if (!glfwInit())
	{
		std::cout << "Error! Failed to initialize GLFW!" << std::endl;
		return false;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL failed to initialize!" << std::endl;
		SDL_Quit();
		return false;
	}


	w_pr_Window = glfwCreateWindow(w_pr_Width, w_pr_Height, w_pr_WindowName, NULL, NULL);


	if (!w_pr_Window)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(w_pr_Window);
	glfwSetWindowUserPointer(w_pr_Window, this);

	glewExperimental = GL_TRUE;

	glfwSetWindowSizeCallback(w_pr_Window, window_Resize);
	glfwSetKeyCallback(w_pr_Window, key_callback);
	glfwSetMouseButtonCallback(w_pr_Window, mouse_button_callback);
	glfwSetCursorPosCallback(w_pr_Window, cursor_poistion_callback);
	glfwSwapInterval(0);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Could not initialize GLEW!" << std::endl;
		return false;
	}


	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glewExperimental = GL_TRUE;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::cout << "3D Test - OPENGL" << std::endl;
	std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Window width and height: " << w_pr_Width << " , " << w_pr_Height << std::endl;

	return true;
}


void window_Resize(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	win->w_i_pr_Keys[key].isPressed = action != GLFW_RELEASE;

}

void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
{
	Window * win = (Window*)glfwGetWindowUserPointer(window);
	win->w_i_pr_MouseButtonKeys[button].isPressed = action != GLFW_RELEASE;
}

void cursor_poistion_callback(GLFWwindow * window, double xpos, double ypos)
{
	Window * win = (Window*)glfwGetWindowUserPointer(window);

	win->w_i_pr_MouseX = xpos;
	win->w_i_pr_MouseY = ypos;
}



