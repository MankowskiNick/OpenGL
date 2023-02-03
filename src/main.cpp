#define GLFW_INCLUDE_NONE

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Shader.h>
#include <gllib.h>
#include <texture.h>
#include <camera.h>
#include <iostream> 
#include <math.h>

Camera* global_camera = NULL;
GLLib* gl_lib = NULL;
GLFWwindow* window = NULL;

double last_mousex;
double last_mousey;


void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}
 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (action == GLFW_REPEAT) // TODO: Fix this to smooth out input.  It is currently functional, but not great.
        global_camera->Walk(key);
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    double dx = xpos - last_mousex;
    double dy = ypos - last_mousey;

    global_camera->UpdateLookDirection(dx, dy);
    last_mousex = xpos;
    last_mousey = ypos;
}

int main(void)
{
    
    gl_lib = new GLLib;
    if (!gl_lib->Init(window, "OpenGL Boiler", 640, 480, error_callback, key_callback, mouse_callback)) 
        return 1;
    gl_lib->BindShader("shaders/shader.vsh", "shaders/shader.fsh");

    // GLFW & Glad loaded
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
    };
    float vertices_ebo[] = {
        // Coords             // Texture Coords
        0.5f,  0.5f, 0.5f,    1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.5f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, // top left 


        0.5f,  0.5f, -0.5f,    1.0f, 1.0f, // top right
        0.5f, -0.5f, -0.5f,    1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f // top left 
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3,   // second triangle

        4, 5, 7,
        5, 6, 7,
    };

    float vertices_cube[] = {
        // Coords               // Texture Coords
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f
    };

    // Maybe we can abstract this differently, or pass in a function to handle this for
    gl_lib->BufferVertices(vertices, sizeof(vertices), 3);

    gl_lib->BufferVerticesWithTextureCoords(vertices_ebo, sizeof(vertices_ebo));
    gl_lib->BufferIndices(indices, sizeof(indices));

    gl_lib->BufferVerticesWithTextureCoords(vertices_cube, sizeof(vertices_cube));

    gl_lib->SwapVAO(2);

    // Textures
    Texture texture1("resources/container.jpg", gl_lib, 0, GL_TEXTURE1, "tex1");
    Texture texture2("resources/bradley.jpeg", gl_lib, 1, GL_TEXTURE2, "tex2");
    Texture texture3("resources/missing_texture.jpg", gl_lib, 2, GL_TEXTURE3, "tex3");

    // Create a projection matrix
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)gl_lib->GetWidth() / (float)gl_lib->GetHeight(), 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    Camera camera = Camera(1.0f, 0.0f, 0.0f);
    global_camera = &camera;

    gl_lib->shader.SetMat4f("projMatrix", proj);
    gl_lib->shader.SetMat4f("modelMatrix", model);
    gl_lib->shader.SetMat4f("viewMatrix", camera.GetView());

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f), 
        glm::vec3( 2.0f,  5.0f, -15.0f), 
        glm::vec3(-1.5f, -2.2f, -2.5f),  
        glm::vec3(-3.8f, -2.0f, -12.3f),  
        glm::vec3( 2.4f, -0.4f, -3.5f),  
        glm::vec3(-1.7f,  3.0f, -7.5f),  
        glm::vec3( 1.3f, -2.0f, -2.5f),  
        glm::vec3( 1.5f,  2.0f, -2.5f), 
        glm::vec3( 1.5f,  0.2f, -1.5f), 
        glm::vec3(-1.3f,  1.0f, -1.5f)  
    };
    float i = 0.0f;
    //main while loop
    while (!glfwWindowShouldClose(window))
    {
        i += 0.01;

        //camera.UpdatePos(6.0f * cos(i), 0.0f, 6.0f * sin(i) );
        camera.Step();
        gl_lib->shader.SetMat4f("viewMatrix", camera.GetView());

        // Clear the screen
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw code
        for (int i = 0; i < 10; i++) {
            
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(0.0f, 1.0f, 1.0f));
            gl_lib->shader.SetMat4f("modelMatrix", model);
            
            gl_lib->DrawTriangles(36);
        }

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
 
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}