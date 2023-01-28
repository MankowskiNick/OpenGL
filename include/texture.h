#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Texture {
    public:

        Texture() {}

        Texture(const std::string& pathname, GLLib* gl_lib, int new_id, unsigned int gl_texture, const char* uniform) {
            LoadFile(pathname, gl_lib, new_id, gl_texture, uniform);
        }

        ~Texture() {}

        // Don't allow use of gl_texture = GL_TEXTURE0
        void LoadFile(const std::string& pathname, GLLib* gl_lib, int new_id, unsigned int gl_texture, const char* uniform) {

            stbi_set_flip_vertically_on_load(true);  
            
            glGenTextures(1, &texture);

            data = stbi_load(pathname.c_str(), &width, &height, &num_channels, 0);
            
            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);  
                glGenerateMipmap(GL_TEXTURE_2D);
            } else {
                std::cout << "ERROR: Failed to load texture: " << pathname << "\n";
            }

            id = new_id;

            glActiveTexture(gl_texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            stbi_image_free(data);

            Activate(gl_lib, uniform);
        }

        void Activate(GLLib* gl_lib, const char* uniform) {    
            gl_lib->shader.SetInt(uniform, id);
        }
        

    private:
        int id;
        unsigned int texture;
        int width, height, num_channels;
        unsigned char* data;

};

#endif