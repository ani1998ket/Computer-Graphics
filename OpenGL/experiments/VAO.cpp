#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "src/utils.hpp"
#include "src/Window.hpp"
#include "src/Objects.hpp"

void readData( float*& data, int& len, const char* path);

int main(){

    Window window(640, 480, "VAO");
    
    float* vertex;
    int vertexCount;
    readData( vertex, vertexCount, "res/vertex.txt" );

    float* vertex2;
    int vertexCount2;
    readData( vertex2, vertexCount2, "res/vertex2.txt" );

    GLuint VAO[2];
    glGenVertexArrays(2, VAO);
    glBindVertexArray(VAO[0]);
   
    {
        glBindVertexArray(VAO[0]);
        GLuint buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer( GL_ARRAY_BUFFER, buffer );
        glBufferData( GL_ARRAY_BUFFER, 6 * vertexCount * sizeof(float), vertex, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0 );
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
    }

    {
        glBindVertexArray(VAO[1]);
        GLuint buffer2;
        glGenBuffers(1, &buffer2);
        glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
        glBufferData( GL_ARRAY_BUFFER, 6 * vertexCount2 * sizeof(float), vertex2, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0 );
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void*)(3 * sizeof(float)));
    }

    Shader vshader(GL_VERTEX_SHADER, "res/shaders/basic_shader.vs");
    Shader fshader(GL_FRAGMENT_SHADER, "res/shaders/basic_shader.fs");
    Program program( vshader, fshader);
    program.use();

    glClearColor(0.5, 0.5, 0.5, 1.0);

    int index = 1;

    while( window.isRunning() ){
        glClear( GL_COLOR_BUFFER_BIT );
        index = (index + 1) % 60;
        glBindVertexArray(VAO[index / 30]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.update();
    }

    delete[] vertex;
    return 0;
}

void readData( float*& data, int& size, const char* path){
    std::ifstream file(path);
    file >> size;
    data = new float[6 * size];
    for( int i = 0; i < size * 6; i++ ){
        file >> data[i];
    }
}