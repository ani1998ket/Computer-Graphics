#include <GLFW/glfw3.h>

class Buffer{
    public:
    GLuint index;

    Buffer() = delete;
    Buffer(void*, unsigned int, GLenum target = GL_ARRAY_BUFFER, GLenum usage = GL_STATIC_DRAW);
};
class Shader{
    public:
    GLuint index;
    Shader() = delete;
    Shader(GLenum type, const char* path);
};
class Program{
    public:
    GLuint index;
    Program() = delete;
    Program( Shader vertex, Shader fragment);

    void use();
};