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
#include "Signature.h"
#include "TextureLoader.h"

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
    //Signature
    //--    
    Signature signature; 
    GLuint signatureTexture = LoadTexture("../../assets/signature.png");
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
        -0.5f, 0.0f, -0.5f,     0.0f, 0.0f,
         0.5f, 0.0f,-0.5f,      1.0f, 0.0f,
        -0.5f, 0.0f, 0.5f,      0.0f, 1.0f,

        //from my understanding to make this a plain
        0.5f, 0.0f, -0.5f,      1.0f, 0.0f,
        0.5f, 0.0f, 0.5f,       1.0f, 1.0f,
       -0.5f, 0.0f, 0.5f,       0.0f, 1.0f
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //plain texture
    GLuint grassTexture = LoadTexture("../../assets/grass.png");

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

        glUniform1i(glGetUniformLocation(program, "useTexture"), true);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, grassTexture);
        glUniform1i(glGetUniformLocation(program, "texture1"), 0);
        //glUniform1i(glGetUniformLocation(program, "useTexture"), false);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //signature
        glUniform1i(glGetUniformLocation(program, "useTexture"), true);
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 1.5f, 1.0f));
        signature.Draw(program, signatureTexture, model);

        //cube 
        //glm::mat4 cubeModel = glm::mat4(1.0f);
        //cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 1.0f, -3.0f));
        //cubeModel = glm::rotate(cubeModel, (float)glfwGetTime(), glm::vec3(0, 1, 0));
        //glUniform1i(glGetUniformLocation(program, "useTexture"), false);
       

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
