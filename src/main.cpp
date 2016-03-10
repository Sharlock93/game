#define GLEW_STATIC //Note(sharo): use static library 
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <bitset>

const char* vsource = "\
#version 330 core\n\
in vec2 point;\
void main() {\
    gl_Position = vec4(point, 0, 1);\
}";

const char* fsource = "\
#version 330 core\n\
out vec4 color;\
void main() {\
    gl_FragColor = vec4(1, 1, 1, 1);\
}";

GLFWwindow* init() {
    std::cout << "GLFW: " << (glfwInit() == GL_TRUE) << std::endl;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    GLFWwindow* window = glfwCreateWindow(500, 500, "Tri", NULL, NULL); 
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE; 

    std::cout << "GLEW: " << glewInit()  << std::endl; 

    return window;
}

void makeProgramAndShaders() {
    GLuint prog =  glCreateProgram(); //Note(sharo): if success will return non zero.
    std::cout << "Program ID: " << prog << std::endl;

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    std::cout << "VShader ID: " << vertex  << std::endl;

    glShaderSource(	vertex, 1, &vsource, NULL); 
    glCompileShader(vertex); //Note(sharo): compile shader

    GLint vshaderstat;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vshaderstat);

    if (vshaderstat != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(vertex, 1024, &log_length, message);
        std::cout << message << std::endl;
    }



    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    std::cout << "FShader ID: " << fragment  << std::endl;

    glShaderSource(	fragment, 1, &fsource, NULL); 
    glCompileShader(fragment); //Note(sharo): compile shader

    GLint fshaderstat;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &fshaderstat);

    if (fshaderstat != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(fragment, 1024, &log_length, message);
        std::cout << message << std::endl;
    }

    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);

    glUseProgram(prog);

    GLint program_linked;
    glGetProgramiv(prog, GL_LINK_STATUS, &program_linked);
    if (program_linked != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(prog, 1024, &log_length, message);
        // Write the error to a log
        std::cout << message << std::endl;
    }

}

struct vec2 {
    float x;
    float y;
};

int main(int argc, char *argv[]) {
 
    char test[] = "hello";
    test[5] = 'a';
    test[6] = (char)NULL;
    test[7] = (char)NULL;
    std::cout << test << std::endl;
    std::cout << sizeof(test) << std::endl;

    
    
    // std::cout << (&a) << std::endl;

#if 0 
    GLFWwindow *window = init();

    bool run = true;

    vec2 data[] = {{0.0, 0.0}, {0.5, 0.5}};

    makeProgramAndShaders();


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); 
    GLuint vbo = 0;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), (void*) &data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    //Note(sharo): new line

    glPointSize(4);
    
    while(run) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            run = false;
        }

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawArrays(GL_POINTS, 0, 2);
        glfwSwapBuffers(window);   

        glfwPollEvents();
    }
#endif

    return 0;
}
