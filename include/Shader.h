#pragma once

#include "../include/glad/glad.h"

class Shader
{
    unsigned id;

    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        void use();
};