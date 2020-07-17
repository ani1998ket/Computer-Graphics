#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "Objects.hpp"

int main(){
    Window window(640, 480, "Square");
   
    float positions[12] = {
        -0.5, -0.5,
         0.5, -0.5,
         0.5,  0.5,

        -0.5, -0.5,
        -0.5,  0.5,
         0.5,  0.5,
    };

    Buffer buffer( positions, 12 * sizeof(float));

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    Shader vertex_shader(GL_VERTEX_SHADER, "shader.vs" );
    Shader fragment_shader(GL_FRAGMENT_SHADER, "shader.fs" );
    Program program( vertex_shader, fragment_shader );
    program.use();

    while( !window.isClosed() ){
        glDrawArrays( GL_TRIANGLES, 0, 6);

        window.update();
    }
}

