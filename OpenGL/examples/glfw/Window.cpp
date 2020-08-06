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
    std::cout << "Window created\n";
}
Window::~Window() {
    glfwDestroyWindow(window);
    std::cout << "Window destroyed\n";
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
    swapBuffers();
    pollEvents();
}