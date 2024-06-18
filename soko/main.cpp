#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cstdio>

void glfw_errorcallback(int error, const char* desc) {
    fprintf(stderr, "GLFW ERR [%d]: %s", error, desc);
}


int main() {
    glfwSetErrorCallback(glfw_errorcallback);
    
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "titol", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "GLAD ERR: init failed");
        glfwTerminate();
        return -1;
    }

    int glvers[2] = { -1, -1 };
    glGetIntegerv(GL_MAJOR_VERSION, &glvers[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glvers[1]);
    printf("Using OpenGL %d.%d", glvers[0], glvers[1]);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
