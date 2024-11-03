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

#include <chrono>

#include "Game/Game.h"

#include"Render/Renderer.h"

glm::ivec2 g_windowSize(13*16, 14*16);
std::unique_ptr<Game>g_game = std::make_unique<Game>(g_windowSize);
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

    const float map_aspect_ratio = static_cast<float>(g_game->getCurrentLevelWidth() / g_game->getCurrentLevelHeight());
    //static_cast<float>( g_game->getCurrentLevelWidth() / g_game->getCurrentLevelHeight());
    unsigned int viewPortWidth = g_windowSize.x;
    unsigned int viewPortHeight = g_windowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;
    if (static_cast<float>(g_windowSize.x) / g_windowSize.y > map_aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>( g_windowSize.y * map_aspect_ratio);
        viewPortLeftOffset = (g_windowSize.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(g_windowSize.x / map_aspect_ratio);
        viewPortBottomOffset = (g_windowSize.y - viewPortHeight) / 2;

    }

    RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight,viewPortLeftOffset,viewPortBottomOffset);
}

//create key action function 
void glfwKeyCallback(GLFWwindow* window, int key, int scanecode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    g_game->setKey(key, action);
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
    RenderEngine::Renderer::setDepthTest(true);

    {

        ResourceManger::setExecutablePath(argv[0]);
        g_game->init();
        glfwSetWindowSize(window,static_cast<int>( g_game->getCurrentLevelWidth()),static_cast<int>( g_game->getCurrentLevelHeight()));
        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            auto curerentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(curerentTime - lastTime).count();
            lastTime = curerentTime;
            g_game->update(duration);
            /* Render here */
            RenderEngine::Renderer::clear();
            g_game->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        g_game = nullptr;
        ResourceManger::unloadAllResources();
    }
    glfwTerminate();
    return 0;
}