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
    gl_lib->BindShader("shaders/shader.vsh", "shaders/shader.fsh");

    // GLFW & Glad loaded

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    float vertices2[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };
    /*
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);  
    */

    gl_lib->BufferVertices(vertices, sizeof(vertices), 3);

    gl_lib->BufferVertices(vertices2, sizeof(vertices2), 3);
    gl_lib->BufferIndices(indices, sizeof(indices));

    gl_lib->BufferVertices(vertices, sizeof(vertices), 3);

    gl_lib->SwapVAO(1);

    //main while loop
    while (!glfwWindowShouldClose(window))
    {

        //glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(float) / 3); // Draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Draw rectangle using the EBO

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}