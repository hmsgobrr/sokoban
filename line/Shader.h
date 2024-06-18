#ifndef SHADER_H
#define SHADER_H

#include <unordered_map>
#include <string>

class Shader {
public:
	int create_from_file(const char* vshader_path, const char* fshader_path);
	void destroy();
	void use();
	void unuse();

	void set_uniform(const char* name, bool value);
	void set_uniform(const char* name, int value);
	void set_uniform(const char* name, float value);
	void set_uniform(const char* name, float x, float y, float z, float w);
private:
	unsigned int m_pid;
	std::unordered_map<const char*, int> m_uniloc_cache;

	int m_compilesuccess;
	char m_compileerrlog[512];

	std::string load_from_file(const char* file_path);
	unsigned int compile_shader(unsigned int shader_type, const std::string& src);
	unsigned int create_shader(const std::string& vshader_source, const std::string& fshader_source);
	int get_uniloc(const char* name);
};

#endif // !SHADER_H
