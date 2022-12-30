#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <glad/glad.h>

class Shader {
    public:
        Shader() {}

        Shader(const std::string& vert_shader_file, const std::string& frag_shader_file) {
            CompileShader(vert_shader_file, frag_shader_file);
        }

        ~Shader() {
            glDeleteShader(vShader);
            glDeleteShader(fShader);
        }

        unsigned int GetProgramID() {
            return id;
        }

        void CompileShader(const std::string& vert_shader_file, const std::string& frag_shader_file) {
            std::string load_error_msg = "";

            std::string vert_shader_source = "";
            LoadSource(GL_VERTEX_SHADER, vert_shader_source, vert_shader_file, load_error_msg);
            std::string frag_shader_source = "";
            LoadSource(GL_FRAGMENT_SHADER, frag_shader_source, frag_shader_file, load_error_msg);

            if (load_error_msg != "") {
                std::cout << "ERROR: Failed to load one or more source files.\n" << load_error_msg;
                exit(1);
            }

            id = CreateShader(vert_shader_source, frag_shader_source);
        }
    private:
        unsigned int id, vShader, fShader;
        
        void LoadSource(const unsigned int type, std::string& source, const std::string& file_name, std::string &error_msg) {
            std::ifstream fin;
            if (type == GL_VERTEX_SHADER) {
                fin.open(file_name.data());
                if (!fin.is_open()) {
                    error_msg += "Error: Vertex shader source file doesn't exist.  (" + file_name + ") \n";
                    fin.close();
                    return;
                }
            }
            else if (type == GL_FRAGMENT_SHADER) {
                fin.open(file_name.data());
                if (!fin) {
                  error_msg += "Error: Fragment shader source file doesn't exist.  (" + file_name + ") \n";
                  fin.close();
                  return;
                }
            }
            while (!fin.eof()) {
                std::string tmp;
                getline(fin, tmp);
                source += tmp + "\n";
            }
            fin.close();
        }

        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
            unsigned int program = glCreateProgram();
            unsigned int vShader = Compile(GL_VERTEX_SHADER, vertexShader);
            unsigned int fShader = Compile(GL_FRAGMENT_SHADER, fragmentShader);

            // Link shaders into one program
            glAttachShader(program, vShader);
            glAttachShader(program, fShader);

            glLinkProgram(program);

            glValidateProgram(program);

            glDeleteShader(vShader);
            glDeleteShader(fShader);

            return program;
        }

        unsigned int Compile(unsigned int type, const std::string& source) {
            unsigned int id = glCreateShader(type);
            const char* src = &source[0];
            glShaderSource(id, 1, &src, NULL);
            glCompileShader(id);

            // Error Handling
            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);

            if (result == GL_FALSE) {
                std::cout << "Error compiling shaders.\n";
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* message = (char*)alloca(length * sizeof(char));

                glGetShaderInfoLog(id, length, &length, message);

                std::cout << message << "\n";

                glDeleteShader(id);
                return 0;
            }

            return id;
        }
};

#endif