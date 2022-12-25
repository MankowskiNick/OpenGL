//#include <glm>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <gllib.h>
#include <iostream> 
 
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
    gl_lib->BindShader("src/shader.vsh", "src/shader.fsh");

    // GLFW & Glad loaded

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    /*float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };*/

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };  

    // Create VBO, VAO, & EBO
    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO); // I'm not entirely sure what a VAO is or what it is used for, but this doesn't work without it.
    glBindVertexArray(VAO); // Read above line

    glGenBuffers(1, &VBO); // Generate a vertex buffer object.  The VBO is the data stream that we use to send data to the GPU memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the VBO so that it is the current buffer

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // Send the indices to the GPU memory

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Send the 'vertices' array to the GPU memory, making use of the VBO

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // This breaks down the layout of the vertex buffer
    glEnableVertexAttribArray(0);  

    //main while loop
    while (!glfwWindowShouldClose(window))
    {

        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float) / 3); // Draw the triangle
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw rectangle using the EBO

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}