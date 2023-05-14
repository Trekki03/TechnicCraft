#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include "T3D/glfw/inputHandling/KeyHandler.h"

namespace t3d::glfw
{
	class Window
	{
	private:
		GLFWwindow* _window;
		void (*_frameBufferSizeCallback)(GLFWwindow* window, int width, int heigth);
		KeyHandler _keyHandler;

	public:
		/**
		 * @brief Creates a new Window and makes its OpenGL context current
		 * @param title The initial, UTF-8 encoded window title. 
		 * @param width The desired width, in screen coordinates, of the window. This must be greater than zero
		 * @param height The desired height, in screen coordinates, of the window. This must be greater than zero. 
		 * @param monitor The monitor to use for full screen mode, or nullptr for windowed mode. 
		 * @param share The window whose context to share resources with, or nullptr to not share resources. 
		 * @param framebufferSizeCallback callback function for window resizing
		 * @internal Documentation partly taken from https://www.glfw.org/docs/3.3/group__window.html#ga3555a418df92ad53f917597fe2f64aeb
		*/
		Window(const char* title, int width, int height, GLFWmonitor* monitor, GLFWwindow* share, void (*frameBufferSizeCallback)(GLFWwindow* window, int width, int heigth));
		
		/**
		 * @brief terminates GLFWwindow on destruction
		*/
		~Window();

		/**
		 * @brief Processes Window (e.g. Keyinput) must be called every frame
		*/
		void Process();
		
		/**
		 * @brief Makes OpenGL context of Window to current conecext
		*/
		void MakeCurrent();
		
		/**
		 * @brief Swaps buffers of Window
		*/
		void SwapBuffers();

		/**
		 * @brief Returns keyhandler linked to the window
		 * @return keyhandler linked to the window
		*/
		inline KeyHandler& GetKeyHandler() { return _keyHandler; }

		/**
		 * @brief returns if glfwWindowShouldClose is set for window.
		 * @return glfwWindowShouldClose value
		*/
		bool GetWindowShouldCloseFlag();
	};
}