#include "Program.h"

#include <cstdio>

void glfw_errorcallback(int error, const char* desc) {
    fprintf(stderr, "GLFW ERR [%d]: %s\n", error, desc);
}

int Program::init(int winw, int winh, const char* titol) {
    glfwSetErrorCallback(glfw_errorcallback);

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(winw, winh, titol, NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "GLAD ERR: init failed\n");
        glfwTerminate();
        return -1;
    }

    int glvers[2] = { -1, -1 };
    glGetIntegerv(GL_MAJOR_VERSION, &glvers[0]);
    glGetIntegerv(GL_MINOR_VERSION, &glvers[1]);
    printf("Using OpenGL %d.%d\n", glvers[0], glvers[1]);

    m_shader.create_from_file(SHADERS_PATH"/a.vert", SHADERS_PATH"/a.frag");
    m_shader.use();

    float vertices[] = {
         0.5f,  0.5f,  // top right
         0.5f, -0.5f,  // bottom right
        -0.5f, -0.5f,  // bottom left
        -0.5f,  0.5f,  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return 0;
}

bool Program::wsc() {
    return glfwWindowShouldClose(window);
}

void Program::bg(Warna col) {
    glClearColor((float)col.r() / 255.0f, (float)col.g() / 255.0f, (float)col.b() / 255.0f, (float)col.a() / 255.0f);
}

void Program::tick() {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

void Program::shut() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
