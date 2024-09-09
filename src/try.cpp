#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec2.hpp>

#include <iostream>

#include "Render/ShaderProgram.h"

#include "Resources/ResourcesManger.h"

#include "Render/Texture2D.h"

#include "Render/Sprite.h"

#include <vector>

#include "Render/AnimatedSprite.h"

#include <chrono>

#include "Game/Game.h"

#include"Render/Renderer.h"

glm::ivec2 g_windowSize(640, 480);
Game g_game(g_windowSize);
//add call back functon
void error_callback(int error, const char* description)
{
    std::cout << "Eror! " << description << std::endl;
}

//start window size

//function to change size of app
void glfwWindowSizeCallback(GLFWwindow* window, int X,int Y)
{
    g_windowSize.x = X;
    g_windowSize.y = Y;
    RenderEngine::Renderer::setViewport(g_windowSize.x, g_windowSize.y);
}

//create key action function 
void glfwKeyCallback(GLFWwindow* window, int key, int scanecode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    g_game.setKey(key, action);
}

int main(int argc, char** argv)
{
   
    GLFWwindow* window;
     
    //set call back function
    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())return -1;

    //add version controler of opengl and enabled crosplatform of openGl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "DSEngene", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //set function to change size of app
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);

    //set key action function 
    glfwSetKeyCallback(window, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Cant load GLAD" << std::endl;
        return -1;
    }
    glfwSwapInterval(1);
 
    //add output of information adbout local OpenGL
    std::cout << "render: " << RenderEngine::Renderer::getRendererStr() << std::endl;
    std::cout << "OpenGl Version: " << RenderEngine::Renderer::getVersionStr() << std::endl;

    //background color
    RenderEngine::Renderer::setClearColer(0, 0, 0, 1);

    {

        ResourceManger::setExecutablePath(argv[0]);
        g_game.init();
        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            auto curerentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(curerentTime - lastTime).count();
            lastTime = curerentTime;
            g_game.update(duration);
            /* Render here */
            RenderEngine::Renderer::clear();
            g_game.render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        ResourceManger::unloadAllResources();
    }
    glfwTerminate();
    return 0;
}