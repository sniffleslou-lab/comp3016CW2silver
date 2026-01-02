// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "main.h"
#include <direct.h> 
#include "LoadShaders.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
GLuint program;



enum VAO_IDs { Triangles, Indices, Colours, Textures, NumVAOs = 2 };
//vao
GLuint VAOs[NumVAOs];
//buffer types and objects
enum Buffers_IDs { ArraryBuffer, NumBuffers = 4 };
GLuint Buffers[NumBuffers];

///mouse callback
///------
float lastX = 640;
float lastY = 360;
Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
bool firstMouse = true;
//mouse callback
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;  
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
/// -----


int main(int argc, char* argv[])
{

    char cwd[256]; _getcwd(cwd, 256); std::cout << "Working directory: " << cwd << std::endl;
    //Initialise glfw and the window as a objecy 
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "silver", NULL, NULL);
    //success?
    if (window == NULL) {
        cout << "GLFW window did not instantiate\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();
    //mouse
    // --
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // --
    //camera 
    //--
    //Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    //--
    
    //now we are loading the shaders
    ShaderInfo shaders[] = {
        {GL_VERTEX_SHADER, "../../shaders/vertexShader.vert"},
        {GL_FRAGMENT_SHADER, "../../shaders/fragmentShader.frag"},
        {GL_NONE, NULL}
    };
    program = LoadShaders(shaders);
    glUseProgram(program);

    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float vertices[] = {
        -0.5f, 0.0f, -0.5f, //pos 0. x,y,z
         0.5f, 0.0f,-0.5f,//pos
        -0.5f, 0.0f, 0.5f,//pos 2

        //from my understanding to make this a plain
        0.5f, 0.0f, -0.5f, //pos 0. x,y,z
        0.5f, 0.0f, 0.5f,//pos
       -0.5f, 0.0f, 0.5f//pos 2
    };
    //Sets index of VAO
    glGenVertexArrays(NumVAOs, VAOs);
    //Binds VAO to a buffer
    glBindVertexArray(VAOs[0]);
    //Sets indexes of all required buffer objects
    glGenBuffers(NumBuffers, Buffers);

    //Binds vertex object to array buffer
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
    //Allocates buffer memory for the vertices of the 'Triangles' buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Allocates vertex attribute memory for vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //Index of vertex attribute for vertex shader
    glEnableVertexAttribArray(0);

    //Unbinding
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //now the render loop
    while (glfwWindowShouldClose(window) == false)
    {
        ProcessUserInput(window); //takes userinput
        glUseProgram(program);
        //camera matrices
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
        unsigned int viewLoc = glGetUniformLocation(program, "view");
        unsigned int projLoc = glGetUniformLocation(program, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


        //renders
        glClearColor(0.25f, 0.0f, 1.0f, 1.0f);// COLOUR TO DISPLAY
        glClear(GL_COLOR_BUFFER_BIT);//CLEARS THE COLOUR

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //refreshes
        glfwSwapBuffers(window);//swaps buffer colour
        glfwPollEvents();
        
        //camera
        // --
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        //

        //movement
        //--
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard('W', deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard('S', deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard('A', deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard('D', deltaTime);
        //


    }
    glfwTerminate();

    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //resizes window besded on values
    glViewport(0, 0, width, height);
}
void ProcessUserInput(GLFWwindow* WindowIn) {
    //close when exist is pressed
    if (glfwGetKey(WindowIn, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(WindowIn, true);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
