#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "T3D/glfw/inputHandling/KeyHandler.h"
#include "T3D/glfw/Window.h"
#include "T3D/openGlRender/openGlCamera/CameraController.h"
#include "T3D/openGLWrapper/ShaderProgram.h"
#include "T3D/openGLWrapper/Texture2D.h"
#include "Objects/BlockManager.h"
#include "WorldGen/Chunk.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glcorearb.h>
#include <GL/glext.h>


t3d::glfw::Window* window;
bool lastKeyState_V;
bool wireMode = false;
bool firstMouse = true;
t3d::openGlRender::CameraController camController;
float deltaTime = 0.0f, lastFrame = 0.0f;
float cameraSpeed;
float lastX = 400, lastY = 300;
GLenum err;

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void HandleEscInput(bool pressed)
{
    if (pressed)
    {
        window->SetWindowShouldCloseFlag();
    }
}

void HandleVInput(bool pressed)
{
    if (pressed)
    {
        if (lastKeyState_V)
        {
            return;
        }

        lastKeyState_V = true;
        if (wireMode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            wireMode = false;
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            wireMode = true;
        }
    }
    else if (lastKeyState_V)
    {
        lastKeyState_V = false;
    }
}

void HandleWInput(bool pressed)
{
    if (pressed)
    {
        camController.GetActiveCameraPointer()->AddPositionVector(cameraSpeed * camController.GetActiveCameraPointer()->GetDirectionVector());
    }
}

void HandleSInput(bool pressed)
{
    if (pressed)
    {
        camController.GetActiveCameraPointer()->AddPositionVector(-(cameraSpeed * camController.GetActiveCameraPointer()->GetDirectionVector()));
    }
}

void HandleAInput(bool pressed)
{
    if (pressed)
    {
        camController.GetActiveCameraPointer()->AddPositionVector(-(glm::normalize(
            glm::cross(camController.GetActiveCameraPointer()->GetDirectionVector(), glm::vec3(0.0f, 1.0f, 0.0f)))
            * cameraSpeed));
    }
}

void HandleDInput(bool pressed)
{
    if (pressed)
    {
        camController.GetActiveCameraPointer()->AddPositionVector(glm::normalize(
            glm::cross(camController.GetActiveCameraPointer()->GetDirectionVector(), glm::vec3(0.0f, 1.0f, 0.0f)))
            * cameraSpeed);
    }
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = !firstMouse;
    }

    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    camController.GetActiveCameraPointer()->AddYaw(xOffset);
    camController.GetActiveCameraPointer()->AddPitch(yOffset);

}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    camController.GetActiveCameraPointer()->AddFov((float)yOffset);
}


int main()
{
    camController = t3d::openGlRender::CameraController();
    auto cam1 = camController.CreateCamera({ 40.0f, 250.0f, 0.5f }, 0.0f, -155.0f, 45.0f);
    camController.SetActiveCamera(cam1);

    glfwInit();
    //Set OpenGL Context to Version 3.3 core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = new t3d::glfw::Window("Test", 800, 600, nullptr, nullptr, FrameBufferSizeCallback);

    window->GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_ESCAPE, HandleEscInput, "Close");
    window->GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_V, HandleVInput, "WireView");
    window->GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_W, HandleWInput, "W");
    window->GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_A, HandleAInput, "A");
    window->GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_S, HandleSInput, "S");
    window->GetKeyHandler().SetKeyEvent(t3d::glfw::KeyHandler::KeyCode::KEY_D, HandleDInput, "D");

    glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window->GetWindow(), mouse_callback);
    glfwSetScrollCallback(window->GetWindow(), scroll_callback);
    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    while (((err = glGetError()) != GL_NO_ERROR)) {}
    game::BlockManager manager;

    t3d::openGl::ShaderProgram basicShader("res/shader/basic.vert", "res/shader/basic.frag");
    t3d::openGl::Texture2D diffuseMap("res/textures/TextureAtlas.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST,
                                 GL_NEAREST, false);
    t3d::openGl::Texture2D specularMap("res/textures/TextureAtlas.jpg", GL_RGB, GL_RGB, GL_REPEAT, GL_REPEAT, GL_NEAREST,
                                  GL_NEAREST, false);
   
    diffuseMap.SetTextureSlot(0);
    specularMap.SetTextureSlot(1);
    basicShader.SetUniform1i("material.diffuse", 0);
    basicShader.SetUniform1i("material.specular", 1);
    

    glEnable(GL_DEPTH_TEST);
    
    game::Chunk* chunks[4][4];
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            chunks[x][y] = new game::Chunk(&manager);
        }
    }

    while (!window->GetWindowShouldCloseFlag())
    {
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        cameraSpeed = 10.0f * deltaTime;

        window->Process();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camController.GetActiveCameraPointer()->GetFov()), 800.0f / 600.0f, 0.1f, 100.0f);
        basicShader.SetUniformMatrix4fv("projection", false, glm::value_ptr(projection));

        glm::mat4 view;
        view = glm::lookAt(camController.GetActiveCameraPointer()->GetPositionVector(), camController.GetActiveCameraPointer()->GetPositionVector() + camController.GetActiveCameraPointer()->GetDirectionVector(), glm::vec3(0.0f, 1.0f, 0.0f));
        basicShader.SetUniformMatrix4fv("view", false, glm::value_ptr(view));


        //Draw Cubes
        basicShader.Bind();
        basicShader.SetUniform1f("material.shininess", 32.0f);
        basicShader.SetUniform3f("light.position", { 2.0f, 6.0f, 1.0f });
        basicShader.SetUniform3f("light.ambient", { 0.4f, 0.4f, 0.4f });
        basicShader.SetUniform3f("light.diffuse", { 0.5f, 0.5f, 0.5f });
        basicShader.SetUniform3f("light.specular", { 1.0f, 1.0f, 1.0f });
        basicShader.SetUniform3f("viewPos", { camController.GetActiveCameraPointer()->GetPositionVector().x,camController.GetActiveCameraPointer()->GetPositionVector().y,camController.GetActiveCameraPointer()->GetPositionVector().z });
        

        glm::mat4 model;
        for (int cx = 0; cx < 4; cx++)
        {
            for (int cz = 0; cz < 4; cz++)
            {
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(cx * 16, 0, cz * 16));
                basicShader.SetUniformMatrix4fv("model", false, glm::value_ptr(model));

                t3d::openGl::VertexArrayObject* vao = chunks[cx][cz]->GetVao();
                if (vao == nullptr)
                {
                    continue;
                }
                
                vao->Bind();
                glDrawElements(GL_TRIANGLES, vao->GetVertexCount(), GL_UNSIGNED_INT, nullptr);
                vao->Unbind();

                

            }
        }
        basicShader.Unbind();

        std::cout << 1 / deltaTime << "fps" << std::endl;

        window->SwapBuffers();
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
