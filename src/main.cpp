#include <iostream>
#include "../include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "../include/Shader.h"

#define windowWidth 800
#define windowHeight 600

// triangle vertices in NDC (Normalized Device Coordinates x,y,z in [-1,1])
// lets draw a play button shape
// (0,0,0) is center of screen
	
float vertices[] = {
    // location         // color
    0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // top right
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f  // top left 
};
unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

void onFramebufferSizeChanged(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}

void handleInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int main()
{
    glfwInit();

    // set to OpenGL 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    GLFWwindow* window = glfwCreateWindow(windowWidth,windowHeight, "LearnOpenGL", NULL, NULL);
    if(window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // init glad that will get opengl drivers implementations
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell OpenGL the size of our window
    glViewport(0,0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, onFramebufferSizeChanged);
    
    // Vertex Buffer
    unsigned vertexBufferObject;
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex array
    unsigned vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    // Vertex array attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Vertex array element buffer
    // The vertex knows this its element buffer because it is bound
    unsigned int elementsBufferObject;
    glGenBuffers(1, &elementsBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    Shader basicShader = Shader("./shaders/basic/basic.vert", "./shaders/basic/basic.frag");

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // INPUT //
        handleInput(window);

        // RENDER //

        // clear the last frame
        glClear(GL_COLOR_BUFFER_BIT);
        basicShader.use();
        glBindVertexArray(vertexArrayObject);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


        // GO TO NEXT FRAME //

        // show the buffer we drew!
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}