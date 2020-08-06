#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "tools/Window.hpp"
#include "tools/Objects.hpp"

int main(){
    Window window(640, 480, "Hello dot");

    float point[] = { 0.0f, 0.0f, 0.0f };

    GLuint VBO;
    glGenBuffers( 1, &VBO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(point), 0);

    while( !window.isClosed() ){
        
        glDrawArrays( GL_POINTS, 0, 1);
        window.update();
    }
}