#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "T3D/glfw/inputHandling/KeyHandler.h"
#include "T3D/glfw/windowHandling/WindowProcessing.h"

void handleTInput(bool pressed)
{
    if (pressed)
    {
        std::cout << "t pressed" << std::endl;
    }
}

int main()
{
    glfwInit();
    //Set OpenGL Context to Version 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "TechnicCraft", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, t3d::glfw::framebuffer_size_callback);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD Failed" << std::endl;
    }
    glfwSwapInterval(1);

    t3d::glfw::KeyHandler keyHandler{ window };
    std::cout << "Der Handler: " << keyHandler.GetKeyEventName(t3d::glfw::KeyHandler::KeyCode::KEY_T) << " wurde f�r T gesetzt" << std::endl;

    keyHandler.SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_T, handleTInput, "T Handler");
    std::cout << "Der Handler: " << keyHandler.GetKeyEventName(t3d::glfw::KeyHandler::KeyCode::KEY_T) << " wurde f�r T gesetzt" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        keyHandler.ProcessKeyInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
