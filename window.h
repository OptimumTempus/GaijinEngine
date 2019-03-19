#pragma once


#include<gl/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<SDL.h>

#define MAX_KEYS 1024
#define MAX_MOUSEKEYS 32



struct KeyPress
{
	bool isPressed;
};


class Window
{
	friend struct GLFWwindow;
public:
	bool hideMouse;

	Window(const char* wName, int width, int height);
	~Window();

	void w_update();
	bool w_closed() const;
	void clear(float r, float g, float b, float a) const;
	int w_getWidth() const;
	int w_getHeight() const;

	void turnKeyPressOff(unsigned int key);
	void turnkeyPressOn(unsigned int key);

	void turnMousePressOff(unsigned int key);
	void turnMousePressOn(unsigned int key);

	bool w_isKeyPressed(unsigned int key);
	bool w_isMouseButtonPressed(unsigned int buttoncode) const;
	void w_getMousePosition(double &x, double &y) const;
	GLFWwindow* getWindow();


	void toggleMouse();
	inline bool getToggleMouse()
	{
		return hideMouse;
	};

private:
	
	int w_pr_Width, w_pr_Height;
	const char *w_pr_WindowName;
	GLFWwindow *w_pr_Window;
	bool w_pr_Closed;

	//input
	
	KeyPress w_i_pr_Keys[MAX_KEYS];
	KeyPress w_i_pr_MouseButtonKeys[MAX_MOUSEKEYS];
	double w_i_pr_MouseX;
	double w_i_pr_MouseY;


	bool w_pr_Init();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;


	friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	friend static void cursor_poistion_callback(GLFWwindow* window, double xpos, double ypos);


};




