
#include "shader.hpp"

#include <iostream>

namespace tutorial
{

Shader::Shader(const std::string& vertex, const std::string& fragment) noexcept
{
    create(vertex, fragment);
}

bool Shader::create(const std::string& vertex, const std::string& fragment) noexcept
{
    destroy();

    shaderProgram = glCreateProgram();
    if (shaderProgram == 0)
    {
        std::cout << "glCreateProgram error: " << glGetError() << std::endl;
        return false;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (vertexShader == 0)
    {
        std::cout << "glCreateShader(GL_VERTEX_SHADER) error: " << glGetError() << std::endl;
        return false;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentShader == 0)
    {
        std::cout << "glCreateShader(GL_FRAGMENT_SHADER) error: " << glGetError() << std::endl;
        return false;
    }

    {
        const char* data = vertex.c_str();
        glShaderSource(vertexShader, 1, &data, 0);
        glCompileShader(vertexShader);

        const GLenum glError = glGetError();
        if (glError != GL_NO_ERROR)
        {
            std::cout << "glCompileShader(vertexShader) error: " << glError << std::endl;
            return false;
        }
    }

    {
        const char* data = fragment.c_str();
        glShaderSource(fragmentShader, 1, &data, 0);
        glCompileShader(fragmentShader);

        const GLenum glError = glGetError();
        if (glError != GL_NO_ERROR)
        {
            std::cout << "glCompileShader(fragmentShader) error: " << glError << std::endl;
            return false;
        }
    }

    GLint shaderStatus = 0;

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderStatus);

    if (shaderStatus == GL_FALSE)
    {
        std::cout << "glLinkProgram() failed." << std::endl;
        return false;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &shaderStatus);

    if (shaderStatus == GL_FALSE)
    {
        std::cout << "glValidateProgram() failed." << std::endl;
        return false;
    }

    return true;
}

void Shader::destroy() noexcept
{
    glUseProgram(0);

    if (glIsProgram(shaderProgram))
    {
        if (glIsShader(vertexShader))
        {
            glDetachShader(shaderProgram, vertexShader);
        }
        if (glIsShader(fragmentShader))
        {
            glDetachShader(shaderProgram, fragmentShader);
        }
        glDeleteProgram(shaderProgram);
    }
    if (glIsShader(vertexShader))
    {
        glDeleteShader(vertexShader);
    }
    if (glIsShader(fragmentShader))
    {
        glDeleteShader(fragmentShader);
    }

    shaderProgram = 0;
    vertexShader = 0;
    fragmentShader = 0;
}

bool Shader::isCreated() const noexcept
{
    return shaderProgram > 0 && vertexShader > 0 && fragmentShader > 0;
}

GLint Shader::getUniform(const std::string& uniformName) const noexcept
{
    return isCreated() ? glGetUniformLocation(shaderProgram, uniformName.c_str()) : 0;
}

GLuint Shader::getAttribute(const std::string& attributeName) const noexcept
{
    return isCreated() ? glGetAttribLocation(shaderProgram, attributeName.c_str()) : 0;
}

void Shader::bind() const noexcept
{
    if (isCreated())
    {
        glUseProgram(shaderProgram);
    }
}

}  // namespace tutorial
