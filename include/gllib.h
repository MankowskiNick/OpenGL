#ifndef gllib_h
#define gllib_h

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <Shader.h>

#include <utility>
#include <functional>

class GLLib {
    public:
        GLLib() { 
            VAOs = new GLuint;
            VBOs = new GLuint;
            EBOs = new GLuint;
            
            VAOs_size = 0;
            VBOs_size = 0;
            EBOs_size = 0;
        }
        ~GLLib() { }

        bool Init(GLFWwindow*& window, 
            const char* window_name, 
            const int window_width,
            const int window_height,
            void (*error_callback_func)(int, const char*) = NULL, 
            void (*key_callback_func)(GLFWwindow*, int, int, int, int) = NULL,
            void (*mouse_callback_func)(GLFWwindow*, double, double) = NULL
        ) { 
            // Set error callback
            if (error_callback_func != NULL)
                glfwSetErrorCallback(error_callback_func);
            // Init GLFW
            if (!glfwInit()) 
                return false;
        
            // Window hints
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #ifdef __APPLE__ 
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            // Create window
            width = window_width;
            height = window_height;
            window = glfwCreateWindow(width, height, window_name, NULL, NULL);

            // Window creation failure
            if (!window)
            {
                glfwTerminate();
                return false;
            }


            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

            if (key_callback_func != NULL)
                glfwSetKeyCallback(window, key_callback_func);   
            if (mouse_callback_func != NULL)
                glfwSetCursorPosCallback(window, mouse_callback_func);

            // Set OpenGL context
            glfwMakeContextCurrent(window);
            glfwSwapInterval(1);

            // Initialize GLAD
            gladLoadGL();    

            // Glad init failure
            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
                std::cout << "Failed to initialize OpenGL context" << std::endl;
                return false;
            }

            glEnable(GL_DEPTH_TEST);

            return true;

        }
        
        int GetWidth() {
            return width;
        }
        
        int GetHeight() {
            return height;
        }

        bool BindShader(const std::string& vert_shader_file, const std::string& frag_shader_file) {
            try {
                // Compile vertex shader
                shader = Shader(vert_shader_file, frag_shader_file);
                shader.Use();
                return true; 
            }
            catch(...) {
                return false;
            }
        }
        
        void BindKeyCallback(GLFWwindow*& window, void (*key_callback_func)(GLFWwindow*, int, int, int, int)) {
            if (key_callback_func != NULL)
                glfwSetKeyCallback(window, key_callback_func);
        }

        void BindKeyCallback(GLFWwindow*& window, void (*error_callback_func)(int, const char*)) {
            if (error_callback_func != NULL) 
                glfwSetErrorCallback(error_callback_func);
        }

        void BufferVertices(float* vertices_head, int size, int degree = 3) {

            GLuint* new_vao_ptr = AddBuffer(VAOs, VAOs_size);
            glGenVertexArrays(1, new_vao_ptr);
            glBindVertexArray(*new_vao_ptr);

            GLuint* new_vbo_ptr = AddBuffer(VBOs, VBOs_size);
            glGenBuffers(1, new_vbo_ptr);

            glBindBuffer(GL_ARRAY_BUFFER, *new_vbo_ptr); 
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices_head, GL_STATIC_DRAW);
            glVertexAttribPointer(0, degree, GL_FLOAT, GL_FALSE, degree * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        void BufferVerticesWithTextureCoords(float* vertices_head, int size) {
            GLuint* new_vao_ptr = AddBuffer(VAOs, VAOs_size);// TODO: we could abstract away this to an AddVao function, i think it would be more useful
            glGenVertexArrays(1, new_vao_ptr);
            glBindVertexArray(*new_vao_ptr);

            GLuint* new_vbo_ptr = AddBuffer(VBOs, VBOs_size);
            glGenBuffers(1, new_vbo_ptr);

            glBindBuffer(GL_ARRAY_BUFFER, *new_vbo_ptr); 
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices_head, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }

        void BufferIndices(unsigned int* indices_head, int size) {
            GLuint* new_ebo_ptr = AddBuffer(EBOs, EBOs_size);
            glGenBuffers(1, new_ebo_ptr);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *new_ebo_ptr);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices_head, GL_STATIC_DRAW); 
        }

        void SwapVAO(int new_index) {
            GLuint new_vao = *(VAOs + new_index * sizeof(int));
            CurVAO = new_vao;
            glBindVertexArray(new_vao);
        }

        unsigned int GetShaderProgram() {
            return shader.GetProgramID();
        }

        void DrawTrianglesEbo(unsigned int num_vertices) {
            glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, 0); // Draw rectangle using the EBO
        }

        void DrawTriangles(unsigned int num_vertices) {
            glDrawArrays(GL_TRIANGLES, 0, num_vertices);
        }

        GLuint GetVAO() {
            return CurVAO;
        }

        Shader shader;
    private:
        int width, height;

        GLuint* AddBuffer(GLuint* buffer, int& size) {

            GLuint* end_ptr = (buffer + (size * sizeof(GLuint)));
            *end_ptr = GLuint();
            size++;

            return end_ptr;
        }

        GLuint CurVAO;
        GLuint CurVBO;
        GLuint CurEBO;

        GLuint* VAOs;
        GLuint* VBOs;
        GLuint* EBOs;

        int VAOs_size;
        int VBOs_size;
        int EBOs_size;

};

#endif