
#include "sdl_window.hpp"

#ifdef EMSCRIPTEN

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>

#elif defined(WIN32)

#include "opengl.hpp"

#include <ShellScalingAPI.h>
#include <comdef.h>

#endif  // EMSCRIPTEN

#include <iostream>

namespace tutorial
{

#ifdef EMSCRIPTEN

namespace
{

SdlWindow* windowPtr = nullptr;

void setCanvasSize(int width, int height) noexcept
{
    if (windowPtr)
    {
        windowPtr->resize(width, height);
    }
}

EMSCRIPTEN_BINDINGS(my_module)
{
	emscripten::function("setCanvasSize", &setCanvasSize);
}

}  // namespace

#endif  // EMSCRIPTEN

SdlWindow::~SdlWindow() noexcept
{
    destroy();
}

bool SdlWindow::create(const std::string& caption) noexcept
{
    if (window && context)
    {
        return true;
    }

    if (!sdlInitialized)
    {
        sdlInitialized = initializeSdl();
        if (!sdlInitialized)
        {
            return false;
        }
    }

    const Uint32 flags = SDL_WINDOW_OPENGL |
                        SDL_WINDOW_SHOWN |
                        SDL_WINDOW_ALLOW_HIGHDPI |
                        SDL_WINDOW_RESIZABLE;

#ifndef EMSCRIPTEN

    const int windowWidth = 800;
    const int windowHeight = 600;

#else  // EMSCRIPTEN

    /**
    * Create a canvas with the size of parent element. Parent style is fill the window.
    */
    const int windowWidth = int(EM_ASM_INT({ return getCanvasParentWidth(); }));
    const int windowHeight = int(EM_ASM_INT({ return getCanvasParentHeight(); }));

#endif  // !EMSCRIPTEN

    const int x = SDL_WINDOWPOS_CENTERED;
    const int y = SDL_WINDOWPOS_CENTERED;

    window = SDL_CreateWindow(caption.c_str(), x, y, windowWidth, windowHeight, flags);
    if (!window)
    {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
        return false;
    }

    windowScale = getScreenScale();

#ifndef EMSCRIPTEN

    /**
    * Recreate window for current display scale.
    */

    if (windowScale != 1.f)
    {
        SDL_DestroyWindow(window);

        pixelsWidth = int(windowWidth * windowScale);
        pixelsHeight = int(windowHeight * windowScale);

        window = SDL_CreateWindow(caption.c_str(), x, y, pixelsWidth, pixelsHeight, flags);
        if (!window)
        {
            std::cout << "SDL_CreateWindow error: " << SDL_GetError() << std::endl;
            return false;
        }
    }
    else
    {
        pixelsWidth = windowWidth;
        pixelsHeight = windowHeight;
    }

#else  // EMSCRIPTEN

    pixelsWidth = int(windowWidth * windowScale);
    pixelsHeight = int(windowHeight * windowScale);

    windowPtr = this;

#endif  // !EMSCRIPTEN

    this->width = windowWidth;
    this->height = windowHeight;

    context = SDL_GL_CreateContext(window);
    if (!context)
    {
        std::cout << "SDL_GL_CreateContext error: " << SDL_GetError() << std::endl;
        return false;
    }

#ifndef EMSCRIPTEN

    /**
    * Initializing OpenGL functions.
    */

    const GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        std::cout << "glewInit error: " << glewGetErrorString(glewError) << std::endl;
        return false;
    }

#endif  // !EMSCRIPTEN

    return true;
}

void SdlWindow::destroy() noexcept
{
    if (context)
    {
        SDL_GL_DeleteContext(context);
        context = nullptr;
    }

    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    if (sdlInitialized)
    {
        SDL_Quit();
        sdlInitialized = false;
    }
}

void SdlWindow::resize(int widthPixels, int heightPixels) noexcept
{
    if (!window)
    {
        return;
    }

    width = int(widthPixels / windowScale);
    height = int(heightPixels / windowScale);
    pixelsWidth = widthPixels;
    pixelsHeight = heightPixels;

#ifdef EMSCRIPTEN

    SDL_SetWindowSize(window, width, height);

#else  // !EMSCRIPTEN

    SDL_SetWindowSize(window, widthPixels, heightPixels);

#endif  // EMSCRIPTEN

}

int SdlWindow::getWidth() const noexcept
{
    return width;
}

int SdlWindow::getHeight() const noexcept
{
    return height;
}

int SdlWindow::getPixelsWidth() const noexcept
{
    return pixelsWidth;
}

int SdlWindow::getPixelsHeight() const noexcept
{
    return pixelsHeight;
}

void SdlWindow::swapBuffers() noexcept
{
    if (window)
    {
        SDL_GL_SwapWindow(window);
    }
}

float SdlWindow::getScale() const noexcept
{
    return windowScale;
}

void SdlWindow::readSdlMessages() noexcept
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_KEYUP:
                input.pressedKeys.erase(sdlEvent.key.keysym.sym);
                break;

            case SDL_KEYDOWN:
                input.pressedKeys.insert(sdlEvent.key.keysym.sym);
                break;

            case SDL_MOUSEMOTION:
                input.mouseX = sdlEvent.motion.x;
                input.mouseY = sdlEvent.motion.y;
                break;

            case SDL_MOUSEBUTTONDOWN:
                input.mousePressed = true;
                break;

            case SDL_MOUSEBUTTONUP:
                input.mousePressed = false;
                break;

            case SDL_WINDOWEVENT:
                windowEvent(sdlEvent.window);
                break;
        }
    }
}

bool SdlWindow::isQuit() const noexcept
{
    return quit;
}

const SdlWindow::Input& SdlWindow::getInput() const noexcept
{
    return input;
}

float SdlWindow::getScreenScale() const noexcept
{
    if (!window)
    {
        return 1.f;
    }

#ifdef WIN32

    const float DEFAULT_SYSTEM_DPI = 96.f;

    float dpi = 0.f;

    if (SDL_GetDisplayDPI(SDL_GetWindowDisplayIndex(window), nullptr, &dpi, nullptr) != 0)
    {
        dpi = DEFAULT_SYSTEM_DPI;
    }

    return dpi / DEFAULT_SYSTEM_DPI;

#elif defined(EMSCRIPTEN)

    return emscripten_get_device_pixel_ratio();

#else

    return 1.f;

#endif  // WIN32

}

bool SdlWindow::initializeSdl() noexcept
{
    Uint32 initFlags = SDL_INIT_VIDEO;

    /**
    * SDL_INIT_AUDIO cannot be initialized in browser without user action.
    * For example, SDL_Init(SDL_INIT_AUDIO) can be called on a click.
    */

#ifndef EMSCRIPTEN

    /**
    * A trick to enable HDPI support for the app.
    */

    const HRESULT hresult = SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    if (FAILED(hresult))
    {
        _com_error err(hresult);
        std::cout << "SetProcessDpiAwareness error: " << err.ErrorMessage() << std::endl;
    }

    /**
    * Setting OpenGL profile for Windows.
    */

    const int contextProfile{ SDL_GL_CONTEXT_PROFILE_CORE };

#else  // EMSCRIPTEN

    /**
    * Setting OpenGL profile for Emscripten: GLES.
    */
    const int contextProfile{ SDL_GL_CONTEXT_PROFILE_ES };

#endif  // !EMSCRIPTEN

    const int versionOpenGLMajor{ 2 };
    const int versionOpenGLMinor{ 1 };
    const int channelBitsRed{ 8 };
    const int channelBitsGreen{ 8 };
    const int channelBitsBlue{ 8 };
    const int channelBitsAlpha{ 0 };
    const int bufferBitsDepth{ 16 };
    const int bufferBitsStencil{ 0 };

    if (SDL_Init(initFlags) < 0)
    {
        std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, versionOpenGLMajor) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, versionOpenGLMinor) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, contextProfile) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, channelBitsRed) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, channelBitsGreen) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, channelBitsBlue) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, channelBitsAlpha) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, bufferBitsDepth) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, bufferBitsStencil) != 0 ||
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1) != 0)
    {
        std::cout << "SDL_GL_SetAttribute error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void SdlWindow::windowEvent(const SDL_WindowEvent& windowEvent) noexcept
{
    switch (windowEvent.event)
    {
        case SDL_WINDOWEVENT_MOVED:
        {
            const float newScale = getScreenScale();
            if (newScale != windowScale) // This can happen when current display has been changed.
            {
                windowScale = newScale;
                const int newWidth = int(width * newScale);
                const int newHeight = int(height * newScale);
                resize(newWidth, newHeight);
            }
        }
            break;

        case SDL_WINDOWEVENT_RESIZED:
            windowScale = getScreenScale();
            pixelsWidth = windowEvent.data1;
            pixelsHeight = windowEvent.data2;
            width = int(pixelsWidth / windowScale);
            height = int(pixelsHeight / windowScale);
            break;
    }
}

}  // namespace tutorial
