#pragma once

#include "../include/glad/glad.h"
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
    unsigned id;

    public:
        Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
        void use();

        void setInt(const std::string& uniformName, int value);
        void setFloat(const std::string& uniformName, float value);
        void setMatrix4(const std::string& uniformName, const glm::mat4& value);
};