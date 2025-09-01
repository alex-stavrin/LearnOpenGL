#include <iostream>
#include "../include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "../include/Shader.h"
#include "../include/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const unsigned windowWidth = 800;
const unsigned windowHeight =  600;

const float mixValueChangeSpeed = 0.01;
float mixValue = 1.0f;

// triangle vertices in NDC (Normalized Device Coordinates x,y,z in [-1,1])
// (0,0,0) is center of screen
float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mixValue += mixValueChangeSpeed;
        if (mixValue > 1) mixValue = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mixValue -= mixValueChangeSpeed;
        if (mixValue < 0) mixValue = 0;
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

    // flip images loaded in the x axis
    stbi_set_flip_vertically_on_load(true);

    unsigned codingClubTexture;
    unsigned ditTexture;
    int imageWidth, imageHeight, imageNumberOfColorChannels;


    unsigned char* imageBytes = stbi_load("assets/logo.png", &imageWidth, &imageHeight, &imageNumberOfColorChannels, 0);
    if(imageBytes)
    {
        // generate and bind texture object

        glGenTextures(1, &codingClubTexture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, codingClubTexture);
        
        // make texture repeat on x and y
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // texel = pixel in texture

        // what to do when we have more texels than pixels (looking from far. shrunk)
        // linear interpolation will smooth between close texels
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        // what to do when we have more pixels than texels (looking from close. magnified)
        // linear interpolation will smooth between close texels
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // generate the actual texture and its mipmap in the gpu
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        // free the image bytes. we don't need it anymore
        stbi_image_free(imageBytes);
    }
    else
    {
        std::cout << "Failed to load image" << std::endl;
    }

    imageBytes = stbi_load("assets/dit.png", &imageWidth, &imageHeight, &imageNumberOfColorChannels, 0);
    if(imageBytes)
    {
        // generate and bind texture object
        glGenTextures(1, &ditTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, ditTexture);
        
        // make texture repeat on x and y
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // texel = pixel in texture

        // what to do when we have more texels than pixels (looking from far. shrunk)
        // linear interpolation will smooth between close texels
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
        // what to do when we have more pixels than texels (looking from close. magnified)
        // linear interpolation will smooth between close texels
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // generate the actual texture and its mipmap in the gpu
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        // free the image bytes. we don't need it anymore
        stbi_image_free(imageBytes);
    }
    else
    {
        std::cout << "Failed to load image" << std::endl;
    }
    
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader basicShader = Shader("./shaders/basic/basic.vert", "./shaders/basic/basic.frag");
    basicShader.setInt("textureData0", 0);
    basicShader.setInt("textureData1", 1);


    glm::mat4 view = glm::mat4(1.0f);

    glm::vec3 cameraPos = glm::vec3(0.0f,1.0f,3.0f);

    glm::vec3 cameraUp = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 cameraForward = glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraForward));

    view = glm::lookAt(cameraPos, cameraPos + cameraForward, cameraUp);

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

    basicShader.setMatrix4("view", view);
    basicShader.setMatrix4("projection", projection);

    glEnable(GL_DEPTH_TEST);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // INPUT //
        handleInput(window);

        // RENDER //

        // clear the last frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        basicShader.use();
        basicShader.setFloat("mixAmount", mixValue);
        glBindVertexArray(vertexArrayObject);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for(unsigned i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f,0.0f,0.0f));

            basicShader.setMatrix4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        // GO TO NEXT FRAME //

        // show the buffer we drew!
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}