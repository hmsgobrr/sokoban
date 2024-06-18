#include "Shader.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include <string>

int Shader::create_from_file(const char* vshader_path, const char* fshader_path) {
	try {
		const std::string& vshader = load_from_file(vshader_path);
		const std::string& fshader = load_from_file(fshader_path);
		m_pid = create_shader(vshader, fshader);
	}
	catch (std::ifstream::failure e) {
		return -1;
	}
	return 0;
}

void Shader::destroy() {
	glDeleteProgram(m_pid);
}

std::string Shader::load_from_file(const char* file_path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(file_path);
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		return stream.str();
	}
	catch (std::ifstream::failure e) {
		fprintf(stderr, "GL ERR: Failed to read shader file from %s\n", file_path);
		throw e;
	}
}

unsigned int Shader::compile_shader(unsigned int shader_type, const std::string& src) {
	unsigned int shader = glCreateShader(shader_type);
	const char* sors = src.c_str();
	glShaderSource(shader, 1, &sors, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &m_compilesuccess);
	if (!m_compilesuccess) {
		glGetShaderInfoLog(shader, 512, NULL, m_compileerrlog);
		fprintf(stderr, "GL ERR: Failed to compile %s shader, %s\n", (shader_type == GL_VERTEX_SHADER ? "vertex" : "fragment"), m_compileerrlog);
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

unsigned int Shader::create_shader(const std::string& vshader_source, const std::string& fshader_source) {
	unsigned int program = glCreateProgram();
	unsigned int vshader = compile_shader(GL_VERTEX_SHADER, vshader_source);
	unsigned int fshader = compile_shader(GL_FRAGMENT_SHADER, fshader_source);
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &m_compilesuccess);
	if (!m_compilesuccess) {
		glGetProgramInfoLog(program, 512, NULL, m_compileerrlog);
		fprintf(stderr, "GL ERR: Failed to link shader program, %s\n", m_compileerrlog);
		glDeleteProgram(program);
		return 0;
	}

	glDeleteShader(vshader);
	glDeleteShader(fshader);

	return program;
}

void Shader::use() {
	glUseProgram(m_pid);
}

void Shader::unuse() {
	glUseProgram(0);
}

void Shader::set_uniform(const char* name, bool val) {
	glUniform1i(get_uniloc(name), (int)val);
}
void Shader::set_uniform(const char* name, int val) {
	glUniform1i(get_uniloc(name), val);
}
void Shader::set_uniform(const char* name, float val) {
	glUniform1f(get_uniloc(name), val);
}
void Shader::set_uniform(const char* name, float x, float y, float z, float w) {
	glUniform4f(get_uniloc(name), x, y, z, w);
}

int Shader::get_uniloc(const char* name) {
	if (m_uniloc_cache.find(name) != m_uniloc_cache.end())
		return m_uniloc_cache[name];
	
	int loc = glGetUniformLocation(m_pid, name);
	if (loc == -1) {
		printf("GL WARN: Failed to find uniform with name %s\n", name);
	}
	m_uniloc_cache[name] = loc;
	return loc;
}
