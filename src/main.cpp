//#include <glm>
#define GLFW_INCLUDE_NONE

//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <gllib.h>
#include <texture.h>
#include <iostream> 
#include <math.h>
 
void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    GLFWwindow* window = NULL;

    GLLib* gl_lib = NULL;
    gl_lib = new GLLib;
    gl_lib->Init(window, "OpenGL Boiler", error_callback, key_callback);
    gl_lib->BindShader("shaders/shader.vsh", "shaders/shader.fsh");

    // GLFW & Glad loaded
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    float vertices2[] = {
        // Coords             // Texture Coords
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    float texCoords[] = {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
    };

    // Maybe we can abstract this differently, or pass in a function to handle this for
    gl_lib->BufferVertices(vertices, sizeof(vertices), 3);

    gl_lib->BufferVerticesWithTextureCoords(vertices2, sizeof(vertices2));
    gl_lib->BufferIndices(indices, sizeof(indices));

    gl_lib->BufferVertices(vertices, sizeof(vertices), 3);

    gl_lib->SwapVAO(1);

    // Textures
    Texture texture1("resources/container.jpg", gl_lib, 1, GL_TEXTURE2, "tex1");
    Texture texture2("resources/missing_texture.jpg", gl_lib, 2, GL_TEXTURE3, "tex2");

    //main while loop
    while (!glfwWindowShouldClose(window))
    {

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw rectangle using the EBO

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2) + 0.5;
        gl_lib->shader.SetFloat("greenValue", greenValue);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}