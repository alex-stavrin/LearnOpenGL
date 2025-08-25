#include "../include/Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    std::string vertexShaderCode;
    std::string framgentShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    // have files throw exceptions on errors
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexShaderPath);
        fragmentShaderFile.open(fragmentShaderPath);
        
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexShaderCode = vertexShaderStream.str();
        framgentShaderCode = fragmentShaderStream.str();

    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "Shader error: " << e.what() << std::endl;
    }

    const char* vertexShaderCodeChar = vertexShaderCode.c_str();
    const char* fragmentShaderCodeChar = framgentShaderCode.c_str();
    
    // error handling variables
    int success;
    char infoLog[512];

    unsigned vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCodeChar, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Error vertex shader compilation: " << infoLog << std::endl;
    }

    unsigned fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCodeChar, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Error fragment shader compilation: " << infoLog << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);

    // check errors in the linking of the program
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "Error in linking of the shader program: " << infoLog << std::endl;
    }

    // we dont need the shaders anymore. they are inside the shader program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(id);
}