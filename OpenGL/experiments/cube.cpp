#include "includes.h"
#include "res/cube.h"

int main(){
    Window window(640, 480,"Cube");

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    {
        glGenBuffers(1, &VBO);
        glBindBuffer( GL_ARRAY_BUFFER, VBO);
        glBufferData( GL_ARRAY_BUFFER, sizeof(colors) + sizeof(positions), nullptr, GL_STATIC_DRAW);
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof( positions ), &positions[0][0] );
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(positions), sizeof( colors ), &colors[0][0] );

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (const void*)sizeof(positions));
    }
    while( window.isRunning() ){
        glDrawArrays( GL_TRIANGLES, 0, 3);
        window.update();
    }

    return 0;
}
    