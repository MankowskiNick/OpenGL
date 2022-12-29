#ifndef gllib_h
#define gllib_h

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>
#include <Shader.h>

class GLLib {
    public:
        GLLib() {}
        ~GLLib() {}

        bool Init(GLFWwindow*& window, 
            std::string window_name, 
            void (*error_callback_func)(int, const char*) = NULL, 
            void (*key_callback_func)(GLFWwindow*, int, int, int, int) = NULL
        ) {

            
            // Set error callback
            if (error_callback_func != NULL)
                glfwSetErrorCallback(error_callback_func);
            // Init GLFW
            if (!glfwInit()) 
                return false;
                //exit(EXIT_FAILURE);
        
            // Window hints
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            #ifdef __APPLE__ 
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif

            // Create window
            window = glfwCreateWindow(640, 480, window_name.data(), NULL, NULL);
                
            if (key_callback_func != NULL)
                glfwSetKeyCallback(window, key_callback_func);   

            // Window creation failure
            if (!window)
            {
                glfwTerminate();
                return false;
            }

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

            return true;

        }
        
        bool BindShader(const std::string& vert_shader_file, const std::string& frag_shader_file) {
            try {
                // Compile vertex shader
                shader = Shader(vert_shader_file, frag_shader_file);
                glUseProgram(shader.GetProgramID());
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
        
        void BufferData(const std::vector< std::vector<float> >& vertices) {
            int buffer_count = vertices.size();
            //for (int i = 0; i < vertices.size(); i++) {
            //    VAOs.push_back(GLuint());
            //    glGenVertexArrays
            //}
            

        }

    private:
        //std::vector<GLuint> VAOs;
        //std::vector<GLuint> VBOs;
        //std::vector<GLuint> EBOs;

        GLuint* VAOs;
        GLuint* VBOs;
        GLuint* EBOs;

        Shader shader;

        //void (*error_callback_func)(int, const char*);
        //void (*key_callback)(GLFWwindow*, int, int, int, int);
        
        //void processInput(GLFWwindow* window) { // This could be expanded into something else
        //    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
       //        glfwSetWindowShouldClose(window, true);
        //    }
        //}
};

#endif