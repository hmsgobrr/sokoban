#ifndef PROGRAM_H
#define PROGRAM_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "misc.h"

class Program {
public:
	int init(int winw, int winh, const char* titol);
	bool wsc();
	void bg(Warna col);
	void tick();
	void shut();
private:
	GLFWwindow* window;
	unsigned int vao, vbo, ebo;
	Shader m_shader;
};

#endif // !PROGRAM_H
