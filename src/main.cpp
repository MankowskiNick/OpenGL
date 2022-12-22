//#include <glm>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <iostream> 
 
static void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
 
int main(void)
{
    GLFWwindow* window;
 
    // Set error callback
    glfwSetErrorCallback(error_callback);
 
    // Init GLFW
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    // Window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__ 
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
 
    // Create window
    window = glfwCreateWindow(640, 480, "OpenGL Boiler", NULL, NULL);

    // Window creation failure
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    // Set key callback
    glfwSetKeyCallback(window, key_callback);
 
    // Set OpenGL context
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize GLAD
    gladLoadGL();
    
    // Glad init failure
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // GLFW & Glad loaded

    //Binding vertices to vertex buffer object

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    
    // Create VBO & VAO
    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Compile vertex shader
    Shader shader;
    glUseProgram(shader.GetProgramID()); 

    //main while loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}