#include "../include/Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{

}

void Shader::use()
{
    glUseProgram(id);
}