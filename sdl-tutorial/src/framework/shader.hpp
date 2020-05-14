
#pragma once

#include "opengl.hpp"

#include <string>

namespace tutorial
{

class Shader final
{
public:

    Shader() noexcept {};
    explicit Shader(const std::string& vertex, const std::string& fragment) noexcept;

    bool    create(const std::string& vertex, const std::string& fragment) noexcept;
    void    destroy() noexcept;
    bool    isCreated() const noexcept;
    GLint   getUniform(const std::string& uniformName) const noexcept;
    GLuint  getAttribute(const std::string& attributeName) const noexcept;
    void    bind() const noexcept;

private:

    GLuint  shaderProgram { 0 };
    GLuint  vertexShader { 0 };
    GLuint  fragmentShader { 0 };
};

}  // namespace tutorial
