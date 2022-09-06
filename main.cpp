// ALUMNO: Gino Liza 
// PROFESOR: Manuel Loaiza
// CURSO: COMPUTACION GRAFICA
// GRUPO: CCOMP7-1 | PERIODO: 2022-2

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.8f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GINO LIZA R.", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    // (1.1-2) CASA PUNTOS, LINEAS - 7 V
    
    float v_casa_lineas[] = {
        -0.5f, -0.5f, 0.0, // A
        -0.5f, 0.5f, 0.0, // D
        -0.8f, 0.5f, 0.0, // E
        0.0f, 0.9f, 0.0, // G
        0.8f, 0.5f, 0.0, // F
        0.5f, 0.5f, 0.0, // C
        0.5f, -0.5f, 0.0, // B
    };

    // (1.3) CASA CON TRIANGULOS 9

    float v_casa_triangulos[] = {
        -0.5f, -0.5f, 0.0, // A
        -0.5f, 0.5f, 0.0, // D
        0.5f, 0.5f, 0.0, // C
        -0.8f, 0.5f, 0.0, // E
        0.0f, 0.9f, 0.0, // G
        0.8f, 0.5f, 0.0, // F
        0.5f, 0.5f, 0.0, // C
        -0.5f, -0.5f, 0.0, // A
        0.5f, -0.5f, 0.0, // B
    };
        
    // (2.1-2) ESTRELLA CON PUNTOS, LINEAS - 10 V
    float v_estrella_lineas[] = {        
         -0.5f, -0.8f, 0.0f, //A
        -0.31f, -0.21f, 0.0f, //H
        -0.81f, 0.15f, 0.0f, //E
        -0.19f, 0.15f, 0.0f, //F
        0.0f, 0.74f, 0.0f, //D
        0.19f, 0.15f, 0.0f, //G
        0.81f, 0.15f, 0.0f, //C
        0.31f, -0.21f, 0.0f, //J
        0.5f, -0.8f, 0.0f, //B
        0.0f, -0.44f, 0.0f, //I        
    };

    // (2.3) ESTRELLA CON TRIANGULOS - 9 V
    float v_estrella_triangulos[] = {
         -0.5f, -0.8f, 0.0f, //A
         0.0f, 0.74f, 0.0f, //D
         0.31f, -0.21f, 0.0f, //J
         -0.81f, 0.15f, 0.0f, //E
         0.19f, 0.15f, 0.0f, //G
         0.5f, -0.8f, 0.0f, //B
         0.19f, 0.15f, 0.0f, //G
        0.81f, 0.15f, 0.0f, //C
        0.31f, -0.21f, 0.0f, //J
    };

    // (3.1-2) PIZZA PUNTOS, LINEAS
    float v_pizza[] = {
        -0.6f, 0.2f, 0.0f, // A
        -0.6f, -0.2f, 0.0f, // B
        -0.36f, -0.52f, 0.0f, // C
        0.02f, -0.65f, 0.0f, // D
        0.4f, -0.52f, 0.0f, // E
        0.63f, -0.2f, 0.0f, // F
        0.63f, 0.2f, 0.0f, // G
        0.4f, 0.52f, 0.0f, // H
        0.02f, 0.65f, 0.0f, // I
        -0.36f, 0.52f, 0.0f, // J        
        0.02f, 0.0f, 0.0f, // K
        -0.6f, 0.2f, 0.0f, // A
        0.63f, -0.2f, 0.0f, // F
        -0.6f, -0.2f, 0.0f, // B
        0.63f, 0.2f, 0.0f, // G
        -0.36f, -0.52f, 0.0f, // C
        0.4f, 0.52f, 0.0f, // H
        0.02f, -0.65f, 0.0f, // D
        0.02f, 0.65f, 0.0f, // I
        0.4f, -0.52f, 0.0f, // E
        -0.36f, 0.52f, 0.0f, // J
    };
    
    float v_pizza_triangulos[] = {
        0.02f, 0.0f, 0.0f, // K
        -0.6f, 0.2f, 0.0f, // A
        -0.6f, -0.2f, 0.0f, // B
        -0.36f, -0.52f, 0.0f, // C
        0.02f, -0.65f, 0.0f, // D
        0.4f, -0.52f, 0.0f, // E
        0.63f, -0.2f, 0.0f, // F
        0.63f, 0.2f, 0.0f, // G
        0.4f, 0.52f, 0.0f, // H
        0.02f, 0.65f, 0.0f, // I
        -0.36f, 0.52f, 0.0f, // J        
        -0.6f, 0.2f, 0.0f, // A
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    // (1.1-2) CASA CON PUNTOS, LINEAS - 7 V
    //glBufferData(GL_ARRAY_BUFFER, sizeof(v_casa_lineas), v_casa_lineas, GL_STATIC_DRAW);
        
    // (1.3) CASA CON TRIANGULOS - 9 V
    //glBufferData(GL_ARRAY_BUFFER, sizeof(v_casa_triangulos), v_casa_triangulos, GL_STATIC_DRAW);

    // -------------------------------------------------------------------------------------------------------

    // (2.1-2) ESTRELLA CON PUNTOS, LINEAS - 10 V    
    //glBufferData(GL_ARRAY_BUFFER, sizeof(v_estrella_lineas), v_estrella_lineas, GL_STATIC_DRAW);

    // (2.3) ESTRELLA CON TRIANGULOS - 9 V
    //glBufferData(GL_ARRAY_BUFFER, sizeof(v_estrella_triangulos), v_estrella_triangulos, GL_STATIC_DRAW);

    // -------------------------------------------------------------------------------------------------------

    // (3.1-2) PIZZA CON PUNTOS, LINEAS -  V
    //glBufferData(GL_ARRAY_BUFFER, sizeof(v_pizza), v_pizza, GL_STATIC_DRAW);

    // (3.3) PIZZA CON TRIANGULOS - V 11
    glBufferData(GL_ARRAY_BUFFER, sizeof(v_pizza_triangulos), v_pizza_triangulos, GL_STATIC_DRAW);
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glPointSize(8.0);

        // (1.1) CASA CON PUNTOS - 7V        
        //glDrawArrays(GL_POINTS, 0, 7);

        // (1.2) CASA CON LINEAS - 8V
        //glDrawArrays(GL_LINE_LOOP, 0, 7);

        // (1.3) CASA CON TRIANGULOS - 
        //glDrawArrays(GL_TRIANGLES, 0, 9);
                
        // (2.1) Estrella con puntos         
        //glDrawArrays(GL_POINTS, 0, 10);
        
        // (2.2) Estrella con lineas
        //glDrawArrays(GL_LINE_LOOP, 0, 10);

        // (2.3) Estrella con triangulos
        //glDrawArrays(GL_TRIANGLES, 0, 9);

        // (3.1) Pizza con puntos
        //glDrawArrays(GL_POINTS, 0, 11);

        // (3.2) Pizza con lineas
        //glDrawArrays(GL_LINE_LOOP, 0, 10);
        //glDrawArrays(GL_LINES, 11, 10);

        // (3.3) Pizza con triangulos
        glDrawArrays(GL_TRIANGLE_FAN, 0, 12);

        // glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}