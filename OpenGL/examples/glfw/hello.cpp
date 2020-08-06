#include <iostream>
#include <unistd.h>
#include <GLFW/glfw3.h>

using namespace std;

int main(){
    int major, minor, rev;
    glfwGetVersion(&major, &minor, &rev);
    cout << major << " : " << minor << " : " << rev << endl;
    cout << glfwGetVersionString() << endl;

    if( !glfwInit() ){
        cout << "Initialisation error" << endl;
    }

    const struct {
        int width = 640;
        int height = 480;
        const char* title = "Hello World"; 
    } WINDOW;
    GLFWwindow* window = glfwCreateWindow(WINDOW.width, WINDOW.height, WINDOW.title, NULL, NULL);

    while(!glfwWindowShouldClose(window)){ 
        glfwSwapInterval(1);
        glfwSwapBuffers( window ); 
        glfwPollEvents();
    }
    glfwDestroyWindow( window );
    glfwTerminate();
    return 0;
}