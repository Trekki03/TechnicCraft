#include "T3d/glfw/Window.h"
#include <iostream>
#include <string>

namespace t3d::glfw
{
	Window::Window(const char* title, int width, int height, GLFWmonitor* monitor, GLFWwindow* share, void (*frameBufferSizeCallback)(GLFWwindow* window, int width, int heigth))
		: _window(glfwCreateWindow(width, height, title, monitor, share)), _frameBufferSizeCallback(frameBufferSizeCallback), _keyHandler(_window)
	{
		if (_window == nullptr)
		{
			throw std::runtime_error(std::string("Failed to create GLFW window with title") + title);
		}
		glfwMakeContextCurrent(_window);
		glfwSetFramebufferSizeCallback(_window, _frameBufferSizeCallback);
	}

	Window::~Window()
	{
		glfwDestroyWindow(_window);
	}

	void Window::Process()
	{
		_keyHandler.ProcessKeyInput();
	}

	void Window::MakeCurrent()
	{
		glfwMakeContextCurrent(_window);
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(_window);
	}

	void Window::SetWindowShouldCloseFlag()
	{
		glfwSetWindowShouldClose(_window, true);
	}

	bool Window::GetWindowShouldCloseFlag()
	{
		return glfwWindowShouldClose(_window);
	}
}