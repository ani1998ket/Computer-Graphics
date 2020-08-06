#include <iostream>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description){
    std::cerr << "Error:" << description << "\n";
}
int main(){
    glfwSetErrorCallback( error_callback );
    if( !glfwInit() ){
        std::cerr << "GLFW: Initialisation Error\n";
        return -1;
    }
    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle",NULL, NULL );
    if( !window ){
        std::cerr << "GLFW: Window CreationError\n";
        glfwTerminate();
        return -1;
    }
    int width,height;
    glfwMakeContextCurrent( window );
    //glfwGetFramebufferSize(window, &width, &height );
    //glViewport(40, 50, width, height );
    while( !glfwWindowShouldClose(window) ){
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}