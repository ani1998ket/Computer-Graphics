#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.hpp"
#include <iostream>

void gameLoop(Window& );

int main(){
    Window window(640, 480, "MyWindow");
    window.makeCurrent();
    if( glewInit() != GLEW_OK ){
        std::cerr << "GLEW: Initialisation Error.\n";
    }
    std::cout << glGetString( GL_VERSION ) << std::endl;
    float vertex[15] = {
        -0.5f, -0.5f, 1.0, 0.0, 0.0,
         0.0f,  0.5f, 0.0, 1.0, 0.0,
         0.5f, -0.5f, 0.0, 0.0, 1.0,
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15, vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float)*2) );
    glEnableVertexAttribArray(1);
    gameLoop(window);
}

void gameLoop(Window& window){
  while(!window.isClosed()){
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.update();
    }
}