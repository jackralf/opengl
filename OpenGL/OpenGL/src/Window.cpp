#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

Window::Window(std::string name, int width, int height)
	:m_Name(name), m_Width(width), m_height(height)
{
	bool result = init();
	if (!result) {
		std::cout << "window init failed" << std::endl;
		glfwTerminate();
	}
	else {
		std::cout << "window init success" << std::endl;
	}
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::init()
{
	if (!glfwInit())
		return false;

	m_window = glfwCreateWindow(m_Width, m_height, m_Name.c_str(), NULL, NULL);
	if (!m_window)
	{
		return false;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(m_window);

	glfwSetWindowUserPointer(m_window, this);

	glfwSetKeyCallback(m_window, key_callback);
	glfwSetCursorPosCallback(m_window, cursor_position_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	glfwSwapInterval(0);

}

bool Window::closed()
{
	return glfwWindowShouldClose(m_window);
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << action << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	std::cout << xpos << ", " << ypos << std::endl;
	Window* win = (Window*) glfwGetWindowUserPointer(window);
	win->m_MousePosX = xpos;
	win->m_MousePosY = ypos;
}