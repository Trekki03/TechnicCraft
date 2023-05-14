#pragma once
#include <GLFW/glfw3.h>

/**
 * @brief Processes window scaling by scaling opengl context accordingly
*/
namespace t3d::glfw
{
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
}