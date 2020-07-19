#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Objects.hpp"

Buffer::Buffer(void* data, unsigned int size, GLenum target, GLenum usage){
    glGenBuffers(1, &index);
    glBindBuffer(target, index);
    glBufferData(target, size, data, usage);
}

//----------------------

Shader::Shader( GLenum type, const char* path ){
    index = glCreateShader(type);

    std::ifstream source(path);
    std::stringstream ss;
    
    std::string s;
    if (source) {
        ss << source.rdbuf();    
        source.close();
    }
    s = ss.str();

    const char* x = s.c_str();
    glShaderSource(index, 1, &x, NULL);
    glCompileShader(index);

    char log[500];
    int length;
    glGetShaderInfoLog( index, 500, &length, log);
    std::cerr << log;
}

//----------------------

Program::Program( Shader vshader, Shader fshader){
    index = glCreateProgram();
    glAttachShader( index, vshader.index );
    glAttachShader( index, fshader.index );
    glLinkProgram( index );

    glValidateProgram( index );

    GLint error;
    glGetProgramiv(index, GL_VALIDATE_STATUS, &error);
    if( error == GL_FALSE){
        std::cerr << "Program Invalidated" << std::endl;
    }

    char log[500];
    int length;
    glGetProgramInfoLog( index, 500, &length, log);
    std::cerr << log;
}

void Program::use(){
    glUseProgram( index);
}