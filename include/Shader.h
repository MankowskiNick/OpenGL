#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <glad/glad.h>

class Shader {
    public:
        Shader() {
            CompileShader();
        }

        ~Shader() {
            glDeleteShader(vShader);
            glDeleteShader(fShader);
        }

        unsigned int GetProgramID() {
            return id;
        }

        void CompileShader() {
            std::string load_error_msg = "";

            std::string vertexShaderSource = "";
            LoadSource(GL_VERTEX_SHADER, vertexShaderSource, load_error_msg);
            std::string fragmentShaderSource = "";
            LoadSource(GL_FRAGMENT_SHADER, fragmentShaderSource, load_error_msg);

            if (load_error_msg != "") {
                std::cout << "ERROR: Failed to load one or more source files.\n" << load_error_msg;
                exit(1);
            }

            id = CreateShader(vertexShaderSource, fragmentShaderSource);
        }
    private:
        unsigned int id, vShader, fShader;
        
        void LoadSource(const unsigned int type, std::string& source, std::string &error_msg) {
            std::ifstream fin;
            if (type == GL_VERTEX_SHADER) {
                fin.open("src/shader.vsh");
                if (!fin) {
                    error_msg += "Error: Vertex shader source file doesn't exist.  (src/shader.vsh)\n";
                    fin.close();
                    return;
                }
            }
            else if (type == GL_FRAGMENT_SHADER) {
                fin.open("src/shader.fsh");
                if (!fin) {
                    error_msg += "Error: Fragment shader source file doesn't exist.  (src/shader.fsh)\n";
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