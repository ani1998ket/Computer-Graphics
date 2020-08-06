#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "tools/Window.hpp"
#include "tools/Objects.hpp"

struct vec3{
    float x;
    float y;
    float z;
};

int main(){
    Window window(640, 480, "Hello dot");

    vec3 vertex[3];
    vertex[0] = {-0.5, -0.5, 0.0 };
    vertex[1] = { 0.5, -0.5, 0.0 };
    vertex[2] = { 0.0,  0.5, 0.0 };

    GLuint VBO;
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

    while( !window.isClosed() ){
        
        glDrawArrays( GL_LINE_LOOP, 0, 3);
        window.update();
    }
}