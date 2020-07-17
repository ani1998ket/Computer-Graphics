#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "tools/Window.hpp"
#include "tools/Objects.hpp"

int main(){

    Window window(640, 480, "Square");
   
    float positions[8] = {
        -0.5, -0.5,
         0.5, -0.5,
         0.5,  0.5,
        -0.5,  0.5,
    };
    unsigned int index[6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    Buffer buffer( positions,sizeof(float)* 8);
    Buffer ibo( index, 6 * sizeof( unsigned int), GL_ELEMENT_ARRAY_BUFFER);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,2 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    Shader vertex_shader(GL_VERTEX_SHADER, "shaders/shader.vs" );
    Shader fragment_shader(GL_FRAGMENT_SHADER, "shaders/u_shader.fs" );
    Program program( vertex_shader, fragment_shader );
    program.use();

    int location = glGetUniformLocation( program.index, "u_color");

    float t = 0.0;
    float r, g, b, a;

    while( !window.isClosed() ){
        //glClearColor();
        glClear( GL_COLOR_BUFFER_BIT );
        // glDrawArrays( GL_TRIANGLES, 0, 6);

        glUniform4f(location, r, g, b, a);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        r = (float)fabs( sin( t ) );
        g = (float)fabs( cos( 3*t ) );
        b = (float)fabs( (sin( 2*t ) + cos(t)) / 2 );
        a = (float)fabs( sin( 4*t ) * cos(t) );

        t += 0.01;

        window.update();
    }
}

