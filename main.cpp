#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define windowWidth 800
#define windowHeight 600

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

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell OpenGL the size of our window
    glViewport(0,0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, onFramebufferSizeChanged);

    while (!glfwWindowShouldClose(window))
    {
        // INPUT //
        handleInput(window);

        // RENDER //

        // clear the last frame
        glClear(GL_COLOR_BUFFER_BIT);

        // GO TO NEXT FRAME //

        // show the buffer we drew!
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}