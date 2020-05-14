
#include "texture_tutorial_app.hpp"
#include "box_mesh.hpp"

#ifdef WIN32

#include <lodepng.h>

#else  // EMSCRIPTEN

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#endif  // WIN32

#include <iostream>

/**
* Creating the app. This function will be called in main.cpp.
*/
tutorial::IApplication::Ptr createApplication() noexcept
{
    return std::make_unique<tutorial::TextureTutorialApp>();
}

namespace tutorial
{

namespace shader_data
{

const std::string VERTEX_SHADER_SOURCE{
    "#version 100\n"
    "precision highp float;\n"
    "uniform mat4 camera;\n"
    "attribute vec4 vertex;\n"
    "attribute vec2 texcoord;\n"
    "varying vec2 vtexcoord;\n"
    "void main(void) {\n"
        "vtexcoord = texcoord;\n"
        "gl_Position = camera * vertex;\n"
    "}"
};

const std::string FRAGMENT_SHADER_SOURCE{
    "#version 100\n"
    "precision highp float;\n"
    "uniform sampler2D texture;\n"
    "varying vec2 vtexcoord;\n"
    "void main(void) {\n"
        "gl_FragColor = texture2D(texture, vtexcoord);\n"
    "}"
};

}  // namespace shader_data

namespace texture
{

using Pixels = std::vector<uint8_t>;

std::string workspaceDir;

void setupWorkspaceDir(const std::string& cmdPath) noexcept
{
    auto it = std::find(cmdPath.rbegin(), cmdPath.rend(), '\\');
    if (it != cmdPath.rend())
    {
        workspaceDir = std::string(cmdPath, 0, cmdPath.size() - std::distance(cmdPath.rbegin(), it));
    }
}

bool makeTexture(GLuint& texture, const Pixels& pixels, uint32_t width, uint32_t height) noexcept
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    const GLenum glError = glGetError();
    if (glError != GL_NO_ERROR)
    {
        std::cout << "makeTexture error: " << glError << std::endl;
        return false;
    }
    return true;
}

void makeEmptyTexture(GLuint& texture) noexcept
{
    const Pixels pixels = {
        50, 50, 50, 255,
        180, 180, 180, 255,
        180, 180, 180, 255,
        50, 50, 50, 255,
    };

    makeTexture(texture, pixels, 2, 2);
}

#ifdef WIN32

/**
* Loading texture in case of Windows.
*/

void loadTexture(const std::string& fileName, GLuint& texture) noexcept
{
    const std::string fullPath = workspaceDir + fileName;
    Pixels pixels;
    uint32_t width = 0;
    uint32_t height = 0;

    if (lodepng::decode(pixels, width, height, fullPath) == 0)
    {
        if (makeTexture(texture, pixels, width, height))
        {
            std::cout << "Texture loaded: " << fullPath << std::endl;
        }
    }
    else
    {
        std::cout << "Unable to load texture: " << fullPath << std::endl;
    }
}

#else // EMSCRIPTEN

/**
* Loading texture in case of Emscripten.
*/

void loadTexture(const std::string& fileName, GLuint& texture) noexcept
{
    // Creating a empty texture for the future loaded pixels.
    glGenTextures(1, &texture);

    // Downloading with js.
    EM_ASM_({
        Module.loadImage(UTF8ToString($0, $1), $2);
    }, fileName.c_str(), fileName.size(), texture);
}

void textureLoaded(GLuint texture) noexcept
{
    // Callback when texture is loaded.
    std::cout << "Texture loaded: " << texture << std::endl;
}

EMSCRIPTEN_BINDINGS(my_module)
{
	emscripten::function("textureLoaded", &textureLoaded);
}

#endif  // WIN32

}  // namespace texture

bool TextureTutorialApp::initialize(int /*argc*/, char **argv) noexcept
{
    std::cout << "Initialize..." << std::endl;

    texture::setupWorkspaceDir(argv[0]);

    if (!window.create("Texture Tutorial"))
    {
        std::cout << "Unable to create a window." << std::endl;
        return false;
    }

    if (!shader.create(shader_data::VERTEX_SHADER_SOURCE, shader_data::FRAGMENT_SHADER_SOURCE))
    {
        std::cout << "Unable to create a shader." << std::endl;
        return false;
    }

    shader.bind();

    uniformCamera = shader.getUniform("camera");
    uniformTexture = shader.getUniform("texture");
    attribVertex = shader.getAttribute("vertex");
    attribTexCoord = shader.getAttribute("texcoord");

    if (uniformCamera < 0 || uniformTexture < 0 || attribVertex < 0 || attribTexCoord < 0)
    {
        std::cout << "Wrong shader." << std::endl;
        return false;
    }

    /**
    * Load and bind texure.
    */

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(uniformTexture, 0);

    // Creating a placeholder texture while loading needed texture.
    texture::makeEmptyTexture(emptyTextureId);

    // Downloading a texture from server in case of web or from the hard drive in case of Windows.
    texture::loadTexture("retrocastle.png", loadedTextureId);

    /**
    * Create VBO and fill vertices data.
    */
    glGenBuffers(1, &vboBuffer);
    if (vboBuffer == 0)
    {
        std::cout << "glGenBuffers error: " << glGetError() << std::endl;
        return false;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);

    glBufferData(GL_ARRAY_BUFFER,
                vertex_data::box.size() * sizeof(glm::vec4),
                vertex_data::box.data(),
                GL_STATIC_DRAW);

    glEnableVertexAttribArray(attribVertex);
    glEnableVertexAttribArray(attribTexCoord);

    const size_t verticesSize = vertex_data::VERTICES_COUNT * sizeof(glm::vec4);

    glVertexAttribPointer(attribVertex, glm::vec4::length(), GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(attribTexCoord, glm::vec2::length(), GL_FLOAT, GL_TRUE, 0,
        reinterpret_cast<void*>(verticesSize));

    /**
    * Checking OpenGL errors that everything was done correctly.
    */
    const GLenum glError = glGetError();
    if (glError != GL_NO_ERROR)
    {
        std::cout << "GL error: " << glError << std::endl;
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.2f, 0.59f, 0.85f, 1.f);

    std::cout << "App initialized." << std::endl;

    return true;
}

void TextureTutorialApp::destroy() noexcept
{
    std::cout << "Destroy..." << std::endl;

    window.destroy();
}

void TextureTutorialApp::performFrame() noexcept
{
    window.readSdlMessages();

    /**
    * Initialize the camera projection matrix when resizing the window.
    */
    if (viewportWidth != window.getPixelsWidth() || viewportHeight != window.getPixelsHeight())
    {
        viewportWidth = window.getPixelsWidth();
        viewportHeight = window.getPixelsHeight();

        projectionMatrix = glm::perspective(45.f, float(viewportWidth) / viewportHeight, 1.f, 1000.f);

        glViewport(0, 0, viewportWidth, viewportHeight);
    }

    /**
    * Update camera position and view matrix.
    */
    const Uint32 currentMilliseconds = SDL_GetTicks();
    const float delta = (currentMilliseconds - elapsedMilliseconds) / 1000.f;
    elapsedMilliseconds = currentMilliseconds;

    viewMatrix = glm::lookAt({cameraVector, 35.f}, glm::vec3{}, {0.f, 0.f, 1.f});

    const glm::mat4 modelViewMatrix = projectionMatrix * viewMatrix;

    cameraVector = glm::rotate(cameraVector, glm::radians(45.f * delta));

    /**
    * Render.
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(uniformCamera, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));

    glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertex_data::VERTICES_COUNT));

    window.swapBuffers();
}

bool TextureTutorialApp::isAppQuit() noexcept
{
    return window.isQuit();
}

bool TextureTutorialApp::loadTexture() noexcept
{
    return true;
}

}  // namespace tutorial
