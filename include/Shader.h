#pragma once

#include "../include/glad/glad.h"

class Shader
{
    unsigned id;

    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

    void use();
};