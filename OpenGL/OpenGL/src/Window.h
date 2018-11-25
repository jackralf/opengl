#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

class Window
{
public:
	Window(std::string name, int width, int height);
	~Window();

	bool init();
	bool closed();
	void update();
	void clear();

	void getMousePosition(float& x, float& y) { x = m_MousePosX; y = m_MousePosY; };

	friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
private:
	GLFWwindow* m_window;
	std::string m_Name;
	int m_Width;
	int m_height;

	float m_MousePosX;
	float m_MousePosY;
};