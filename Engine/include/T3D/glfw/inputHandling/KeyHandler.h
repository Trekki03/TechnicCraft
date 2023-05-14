#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <array>

namespace t3d::glfw
{
	class KeyHandler
	{
	private:

		const static int USABLE_KEY_COUNT = 97;
		const std::array<unsigned int, USABLE_KEY_COUNT> _glfwKeyMapping = {
		GLFW_KEY_SPACE,
		GLFW_KEY_COMMA,
		GLFW_KEY_MINUS,
		GLFW_KEY_PERIOD,
		GLFW_KEY_ESCAPE,
		GLFW_KEY_ENTER,
		GLFW_KEY_TAB,
		GLFW_KEY_BACKSPACE,
		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_LEFT_ALT,
		GLFW_KEY_RIGHT_SHIFT,
		GLFW_KEY_RIGHT_CONTROL,
		GLFW_KEY_RIGHT_ALT,
		GLFW_KEY_RIGHT,
		GLFW_KEY_LEFT,
		GLFW_KEY_DOWN,
		GLFW_KEY_UP,
		GLFW_KEY_0,
		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
		GLFW_KEY_A,
		GLFW_KEY_B,
		GLFW_KEY_C,
		GLFW_KEY_D,
		GLFW_KEY_E,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_I,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_M,
		GLFW_KEY_N,
		GLFW_KEY_O,
		GLFW_KEY_P,
		GLFW_KEY_Q,
		GLFW_KEY_R,
		GLFW_KEY_S,
		GLFW_KEY_T,
		GLFW_KEY_U,
		GLFW_KEY_V,
		GLFW_KEY_W,
		GLFW_KEY_X,
		GLFW_KEY_Y,
		GLFW_KEY_Z,
		GLFW_KEY_F1,
		GLFW_KEY_F2,
		GLFW_KEY_F3,
		GLFW_KEY_F4,
		GLFW_KEY_F5,
		GLFW_KEY_F6,
		GLFW_KEY_F7,
		GLFW_KEY_F8,
		GLFW_KEY_F9,
		GLFW_KEY_F10,
		GLFW_KEY_F11,
		GLFW_KEY_F12,
		GLFW_KEY_F13,
		GLFW_KEY_F14,
		GLFW_KEY_F15,
		GLFW_KEY_F16,
		GLFW_KEY_F17,
		GLFW_KEY_F18,
		GLFW_KEY_F19,
		GLFW_KEY_F20,
		GLFW_KEY_F21,
		GLFW_KEY_F22,
		GLFW_KEY_F23,
		GLFW_KEY_F24,
		GLFW_KEY_F25
		};
		std::array<std::function<void(bool)>, USABLE_KEY_COUNT> _handlerFunctions{ nullptr };
		std::array<const char*, USABLE_KEY_COUNT> _names = {};
		GLFWwindow* _window;

	public:
		/**
		 * @brief KeyCodes usable by KeyProcessing
		*/
		static enum class KeyCode {
			KEY_SPACE,
			KEY_COMMA,
			KEY_MINUS,
			KEY_PERIOD,
			KEY_ESCAPE,
			KEY_ENTER,
			KEY_TAB,
			KEY_BACKSPACE,
			KEY_LEFT_SHIFT,
			KEY_LEFT_CONTROL,
			KEY_LEFT_ALT,
			KEY_RIGHT_SHIFT,
			KEY_RIGHT_CONTROL,
			KEY_RIGHT_ALT,
			KEY_RIGHT,
			KEY_LEFT,
			KEY_DOWN,
			KEY_UP,
			KEY_0,
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,
			KEY_A,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z,
			KEY_F1,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5,
			KEY_F6,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,
			KEY_F13,
			KEY_F14,
			KEY_F15,
			KEY_F16,
			KEY_F17,
			KEY_F18,
			KEY_F19,
			KEY_F20,
			KEY_F21,
			KEY_F22,
			KEY_F23,
			KEY_F24,
			KEY_F25
		};

	public:
		/**
		 * @brief Creates a new keyhandler, that is linked to a GLFWWindow
		 * @param window glfwWindow, from which keypresses should be handled
		*/
		KeyHandler(GLFWwindow* window);

		/**
		 * @brief Bind a function to a key
		 * @param key Key function should be bound to
		 * @param handlerFunction funtction, that should be executed. Function gets executed every frame. Gets key status as parameter (pressed or released)
		 * @param handlerName Name of the handler. Used for user information only. e.g. Fire, Jump, SetWireFrameView...
		*/
		void SetKeyEvent(KeyCode key, const std::function<void(bool keyPressed)>& handlerFunction, const char* handlerName);

		/**
		 * @brief Returns handler name for a given key
		 * @param key key, information should be gethered for
		 * @return name of the handler if set. If not set "Not Set"
		*/
		[[nodiscard]] const char* GetKeyEventName(KeyCode key);

		/**
		 * @brief Processes key Input. Should be executed every frame e.g. via gameloop
		*/
		void ProcessKeyInput();
	};
}