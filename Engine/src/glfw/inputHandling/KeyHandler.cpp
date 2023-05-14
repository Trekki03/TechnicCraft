#include "T3D/glfw/inputHandling/KeyHandler.h"


namespace t3d::glfw
{
	KeyHandler::KeyHandler(GLFWwindow* window)
		: _window(window)
	{}

	void KeyHandler::SetKeyEvent(KeyCode key, const std::function<void(bool keyPressed)>& handlerFunction, const char* handlerName)
	{
		_handlerFunctions[static_cast<int>(key)] = handlerFunction;
		_names[static_cast<int>(key)] = handlerName;
	}

	const char* KeyHandler::GetKeyEventName(KeyCode key)
	{
		const char* name = _names[static_cast<int>(key)];

		if (name == nullptr)
		{
			return "No Set";
		}

		return name;
	}

	void KeyHandler::ProcessKeyInput()
	{
		for (int i = 0; i < USABLE_KEY_COUNT; i++)
		{
			if (nullptr == _handlerFunctions[i]) { continue; }
			int keyState = glfwGetKey(_window, _glfwKeyMapping[i]);

			if (GLFW_PRESS == keyState)
			{
				_handlerFunctions[i](true);
			}
			else
			{
				_handlerFunctions[i](false);
			}
		}
	}
}