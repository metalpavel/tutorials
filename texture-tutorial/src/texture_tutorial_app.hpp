
#pragma once

#include "framework/iapplication.hpp"
#include "framework/sdl_window.hpp"
#include "framework/shader.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace tutorial
{

class TextureTutorialApp final : public IApplication
{
public:

    bool    initialize(int argc, char **argv) noexcept override;
    void    destroy() noexcept override;
    void    performFrame() noexcept override;
    bool    isAppQuit() noexcept override;

private:

    bool    loadTexture() noexcept;

    SdlWindow   window;
    Shader      shader;

    GLint   uniformCamera{ 0 };
    GLint   uniformTexture{ 0 };
    GLint   attribVertex{ 0 };
    GLint   attribTexCoord{ 0 };

    GLuint  vboBuffer{ 0 };
    GLuint  loadedTextureId{ 0 };
    GLuint  emptyTextureId{ 0 };

    Uint32  elapsedMilliseconds{ 0 };

    int viewportWidth{ 0 };
    int viewportHeight{ 0 };

    float positionOffset{ 1.f };

    glm::mat4 projectionMatrix{};
    glm::mat4 viewMatrix{};

    glm::vec2 cameraVector{35.f, 0.f};
};

}  // namespace tutorial
