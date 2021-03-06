#include <GL/glew.h>
#include <iostream>
#include "Window.hpp"

Window::Window(int width, int height, const char* heading) 
    : width(width), height(height), heading(heading)
{
    if( !glfwInit() ){

    }
    window = glfwCreateWindow(width, height,heading, NULL, NULL);
    if(!window){

    }
    this->makeCurrent();
    if( glewInit() != GLEW_OK ){
        std::cerr << "GLEW: Initialisation Error.\n";
    }

    std::cout << "Window created\n";
}
Window::~Window() {
    glfwDestroyWindow(window);
    std::cout << "Window destroyed\n";
    glfwTerminate();
}

bool Window::isClosed() const {
    return glfwWindowShouldClose(window);
}

GLFWwindow* Window::getContext() const {
    return window;
}

void Window::makeCurrent() const {
    glfwMakeContextCurrent(window);
}

void Window::swapBuffers() const{
    glfwSwapBuffers( window );
}

void Window::pollEvents() const{
    glfwPollEvents();
}
void Window::update() const{
    glfwSwapInterval(1);
    swapBuffers();
    pollEvents();
}