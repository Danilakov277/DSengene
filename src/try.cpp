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

//add pointers besed on traengle
GLfloat point[] =
{
0.0f, 50.f,0.0f,
50.f,-50.f,0.0f,
-50.f,-50.f,0.0f
};

//colors for traengle
GLfloat colars[] =
{
1.0f,0.0f,0.0f,
0.0f,1.0f,0.0f,
0.0f,0.0f,1.0f
};
GLfloat texCord[] =
{
0.5f,1.0f,
1.0f,0.0f,
0.0f,0.0f
};

//add call back functon
void error_callback(int error, const char* description)
{
    std::cout << "Eror! " << description << std::endl;
}

glm::ivec2 g_windowSize(640, 480);
//start window size

//function to change size of app
void glfwWindowSizeCallback(GLFWwindow* window, int X,int Y)
{
    g_windowSize.x = X;
    g_windowSize.y = Y;
    glViewport(0, 0, g_windowSize.x, g_windowSize.y);
}

//create key action function 
void glfwKeyCallback(GLFWwindow* window, int key, int scanecode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
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
    std::cout << "render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGl Version: " << glGetString(GL_VERSION) << std::endl;

    //background color
    glClearColor(1, 1, 0, 1);

    {
        ResourceManger resourceManger(argv[0]);
        auto pDefaultShaderProgram = resourceManger.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "cant create shader program: " << "Defaultshader" << std::endl;
            return -1;
        }
        auto pSpriteShaderProgram = resourceManger.loadShaders("SpriteShader", "res/shaders/vSprite.txt", "res/shaders/fSprite.txt");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "cant create shader program: " << "Spriteshader" << std::endl;
            return -1;
        }

        auto tex = resourceManger.loadTexture("DefayltTextures", "res/textures/map_8x8.png");

        std::vector<std::string> subTexturesNames = { 
            "block",
            "topLeftBlock",
            "topRightBlock",
            "topBlock",
            "bottomLeftBlock",
            "rightBlock",
            "bottomLeftTopRightBlock",
            "bottomRightZeroBlock",
            "bottomRightBlock",
            "topLeftBottomRightBlock",
            "leftBlock",
            "bottomLeftZerroBlock",
            "bottomBlock",
            "topRightZerroBlock",
            "topLeftZerroBlock",
            "woter_1",
            "woter_2",
            "woter_3",
            "beton",
            "bush"};
        auto pTextureAtlas = resourceManger.loatTextureAtlas("DefaultTextureAtlas", subTexturesNames, "res/textures/map_8x8.png", 8, 8);

        auto pSprite = resourceManger.loadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100,"bush");
        pSprite->setPosition(glm::vec2(300.f, 100.f));

        auto pAnimatedSprite = resourceManger.loadAnimatedSprite("NewAnimatedSprite", "DefaultTextureAtlas", "SpriteShader", 100, 100, "bush");
        pAnimatedSprite->setPosition(glm::vec2(300.f, 300.f));
        std::vector<std::pair<std::string, uint64_t>> waterState;
        waterState.emplace_back(std::make_pair<std::string, uint64_t>("woter_1",1000000000));
        waterState.emplace_back(std::make_pair<std::string, uint64_t>("woter_2",1000000000));
        waterState.emplace_back(std::make_pair<std::string, uint64_t>("woter_3",1000000000));

        pAnimatedSprite->insertState("woterState",std::move(waterState));

        pAnimatedSprite->setState("woterState");

        //create buffers for sheders
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint color_vbo = 0;
        glGenBuffers(1, &color_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colars), colars, GL_STATIC_DRAW);

        GLuint texCord_vbo = 0;
        glGenBuffers(1, &texCord_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, texCord_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCord), texCord, GL_STATIC_DRAW);//!!!

        //create array buffer
        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        //enabled layout in shaders and linc thay buffers
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCord_vbo);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->use();
        pDefaultShaderProgram->setInt("tex",0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);


        pDefaultShaderProgram->setMatrix4("projectionMat", projectionMatrix);


        pSpriteShaderProgram->use();
        pSpriteShaderProgram->setInt("tex", 0);
        pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);


        auto lastTime = std::chrono::high_resolution_clock::now();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            auto curerentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(curerentTime - lastTime).count();
            lastTime = curerentTime;
            pAnimatedSprite->update(duration);
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

        
            //sheder draw
            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            tex->bind();

            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            pDefaultShaderProgram->setMatrix4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pSprite->render();
            pAnimatedSprite->render();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}