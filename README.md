# comp3016CW2silver

How to run - > comp3016CW2silver\Silver\x64\Debug -> silver.exe




"Create something which does something in OpenGL"
OpenGL Coursework 2 Prototype

This project is a 3D prototype built in C++ using OpenGL. 
It features an environment that has two textures, one with grass and another with my signature, and finally, camera movement. 

Video link -> https://youtu.be/WzwAMtOtyyk 
GitHub link -> https://github.com/sniffleslou-lab/comp3016CW2silver 
Dependencies
GLFW ( WINDOW + input.)
GLEW ( OpenGL function)
STB Image ( textures )
GLM ( maths Library ) 
Game Description
The user can freely move around a 3D scene:
W/A/S/D for movement
Mouse for the camera

The scene contains
Grass plane
Signature quad
3d environment with perspective camera 

Mechanics are simple. The user is able to move around with the camera. This is done as the movement and camera are tied. 

Rendering is interrogated using VAOs and VBOs, with textures sampled using ‘sampler2D' with the use of the fragment shader.











Screenshots of game running


Testing
Due to the nature of the end project, testing is done by checking that shaders are loading and moving the camera.

I always had issues with visual study with the directory of the the project, so I always used something on the lines like
‘    char cwd[256]; _getcwd(cwd, 256); std::cout << "Working directory: " << cwd << std::endl;’
Which will give the work directory of my code, I will often use code lines like these to give errors in the terminal to check if stuff is connected or working.
‘std::cout << "texture failed to load : " << filepath << std::endl;’ 
Evaluation
The end project in light wording is ‘rather bad’. I had ambitions to make something big, but the changing seasons hit me personally hard, and I decided I would rather just pass with the minimum requirements, being safe with what I have, instead of trying to make something big and realising I am unable to submit anything due to an unfinished mess. 

If given the chance to redo this project, let's say in the summer, if I fail and I mess up, I would probably aim to be ambitious and integrate more features into the project, making the game have grass, trees and a feature.





Testing
Due to the nature of the end project, testing is done by checking that shaders are loading and moving the camera.

I always had issues with visual study with the directory of the the project, so I always used something on the lines like
‘    char cwd[256]; _getcwd(cwd, 256); std::cout << "Working directory: " << cwd << std::endl;’
Which will give the work directory of my code, I will often use code lines like these to give errors in the terminal to check if stuff is connected or working.
‘std::cout << "texture failed to loas : " << filepath << std::endl;’ 
Evaluation
The end project in light wording is ‘rather bad’. I had ambitions to make something big, but the seasons changing hit me personally hard, and I decided I would rather just pass with the minimum requirements, being safe with what I have, instead of trying to make something big and realising I am unable to submit anything due to an unfinished mess. 

If given the chance to redo this project, let's sayin the summer, if I fail and I messed up, I would probably aim to be ambitious and integrate more features into the project, making the game have grass, tress and a feature.


