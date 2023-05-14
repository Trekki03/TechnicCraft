#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "T3D/glfw/inputHandling/KeyHandler.h"
#include "T3d/glfw/Window.h"

void handleTInput(bool pressed)
{
    if (pressed)
    {
        std::cout << "t pressed" << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    glfwInit();
    //Set OpenGL Context to Version 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    t3d::glfw::Window window("Test", 400, 400, nullptr, nullptr, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD Failed" << std::endl;
    }
    glfwSwapInterval(1);

    std::cout << "Der Handler: " << window.GetKeyHandler().GetKeyEventName(t3d::glfw::KeyHandler::KeyCode::KEY_T) << " wurde fuer T gesetzt" << std::endl;

    window.GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_T, handleTInput, "T Handler");
    std::cout << "Der Handler: " << window.GetKeyHandler().GetKeyEventName(t3d::glfw::KeyHandler::KeyCode::KEY_T) << " wurde fuwr T gesetzt" << std::endl;

    while (!window.GetWindowShouldCloseFlag())
    {
        window.Process();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window.SwapBuffers();
        glfwPollEvents();
    }
}
