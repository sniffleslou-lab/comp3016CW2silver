// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "main.h"
using namespace std;

int main(int argc, char* argv[])
{
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
    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float verticles[] = {
        -0.5f,-0.5f,0.0f, //pos 0. x,y,z
        0.5f,-0.5f,0.0f,//pos
        0.0f,0.0f,0.0f//pos 2
    };
    //now the render loop
    while (glfwWindowShouldClose(window) == false)
    {
        ProcessUserInput(window); //takes userinput
        //renders
        glClearColor(0.25f, 0.0f, 1.0f, 1.0f);// COLOUR TO DISPLAY
        glClear(GL_COLOR_BUFFER_BIT);//CLEARS THE COLOUR
        //refreshes
        glfwSwapBuffers(window);//swaps buffer colour
        glfwPollEvents(); 
    }


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
