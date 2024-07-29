#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//add pointers besed on traengle
GLfloat point[] =
{
0.0f, 0.5f,0.0f,
0.5f,-0.5f,0.0f,
-0.5f,-0.5f,0.0f
};

//colors for traengle
GLfloat colars[] =
{
1.0f,0.0f,0.0f,
0.0f,1.0f,0.0f,
0.0f,0.0f,1.0f
};
//sheder for pointers(verteses)
const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

//sheder for colors
const char* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color,1.0);"
"}";

//add call back functon
void error_callback(int error, const char* description)
{
    std::cout << "Eror! " << description << std::endl;
}

//start window size
int MonitorXsize = 640;
int MonitorYsize = 480;

//function to change size of app
void glfwWindowSizeCallback(GLFWwindow* window, int X,int Y)
{
    MonitorXsize = X;
    MonitorYsize = Y;
    glViewport(0, 0, MonitorXsize, MonitorYsize);
}

//create key action function 
void glfwKeyCallback(GLFWwindow* window, int key, int scanecode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int main(void)
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
    window = glfwCreateWindow(MonitorXsize, MonitorYsize, "DSEngene", NULL, NULL);
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

    //compale sheders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, nullptr);
    glCompileShader(fs);

    //linc shaders for sheder program
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vs);
    glAttachShader(shader_program, fs);
    glLinkProgram(shader_program);

    //delite sheders
    glDeleteShader(vs);
    glDeleteShader(fs);

    //create buffers for sheders
    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

    GLuint color_vbo = 0;
    glGenBuffers(1, &color_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colars), colars, GL_STATIC_DRAW);

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

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //sheder draw
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}