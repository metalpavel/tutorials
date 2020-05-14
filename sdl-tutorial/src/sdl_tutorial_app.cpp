
#include "sdl_tutorial_app.hpp"
#include "box_mesh.hpp"

#include <iostream>

/**
* Creating the app. This function will be called in main.cpp.
*/
tutorial::IApplication::Ptr createApplication() noexcept
{
    return std::make_unique<tutorial::SdlTutorialApp>();
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
    "attribute vec4 color;\n"
    "varying vec4 vcolor;\n"
    "void main(void) {\n"
        "vcolor = color;\n"
        "gl_Position = camera * vertex;\n"
    "}"
};

const std::string FRAGMENT_SHADER_SOURCE{
    "#version 100\n"
    "precision highp float;\n"
    "varying vec4 vcolor;\n"
    "void main(void) {\n"
        "gl_FragColor = vcolor;\n"
    "}"
};

}  // namespace shader_data

bool SdlTutorialApp::initialize(int /*argc*/, char ** /*argv*/) noexcept
{
    std::cout << "Initialize..." << std::endl;

    if (!window.create("SDL Tutorial (Use spacebar to shift boxes, mouse button to stop camera rotation)"))
    {
        std::cout << "Unable to create a window." << std::endl;
        return false;
    }

    /**
    * Create shader and initialize locations.
    */
    if (!shader.create(shader_data::VERTEX_SHADER_SOURCE, shader_data::FRAGMENT_SHADER_SOURCE))
    {
        std::cout << "Unable to create a shader." << std::endl;
        return false;
    }

    shader.bind();

    uniformCamera = shader.getUniform("camera");
    attribVertex = shader.getAttribute("vertex");
    attribColor = shader.getAttribute("color");

    if (uniformCamera < 0 || attribVertex < 0 || attribColor < 0)
    {
        std::cout << "Wrong shader." << std::endl;
        return false;
    }

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
    glEnableVertexAttribArray(attribColor);

    const size_t verticesSize = vertex_data::VERTICES_COUNT * sizeof(glm::vec4);

    glVertexAttribPointer(attribVertex, glm::vec4::length(), GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(attribColor, glm::vec4::length(), GL_FLOAT, GL_TRUE, 0,
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

void SdlTutorialApp::destroy() noexcept
{
    std::cout << "Destroy..." << std::endl;

    window.destroy();
}

void SdlTutorialApp::performFrame() noexcept
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

    viewMatrix = glm::lookAt({cameraVector, 55.f}, glm::vec3{}, {0.f, 0.f, 1.f});

    const glm::mat4 modelViewMatrix = projectionMatrix * viewMatrix;

    /**
    * Simply feedback from input.
    */
    if (!window.getInput().mousePressed)
    {
        cameraVector = glm::rotate(cameraVector, glm::radians(45.f * delta));
    }

    if (window.getInput().pressedKeys.count(SDLK_SPACE) > 0)
    {
        positionOffset += 0.5f * delta;
        if (positionOffset > 2.f)
        {
            positionOffset -= 1.f;
        }
    }

    /**
    * Render.
    */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static const std::vector<glm::vec3> boxPositions
    {
        { 0.f, 0.f, 0.f },
        { vertex_data::BOX_SIZE * 2.f, vertex_data::BOX_SIZE * 2.f, 0.f },
        { vertex_data::BOX_SIZE * -2.f, 0.f, 0.f },
        { 0.f, vertex_data::BOX_SIZE * -2.f, 0.f }
    };

    for (auto& position : boxPositions)
    {
        const auto positionMatrix = glm::translate(modelViewMatrix, position * positionOffset);

        glUniformMatrix4fv(uniformCamera, 1, GL_FALSE, glm::value_ptr(positionMatrix));

        glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertex_data::VERTICES_COUNT));
    }

    window.swapBuffers();
}

bool SdlTutorialApp::isAppQuit() noexcept
{
    return window.isQuit();
}

}  // namespace tutorial
