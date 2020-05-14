
#pragma once

#include <SDL.h>

#include <string>
#include <unordered_set>

namespace tutorial
{

class SdlWindow final
{
public:

    struct Input final
    {
        std::unordered_set<uint32_t> pressedKeys;
        bool mousePressed{ false };
        int mouseX{ 0 };
        int mouseY{ 0 };
    };

    SdlWindow() noexcept {};
    ~SdlWindow() noexcept;

    /**
    * Create a window.
    */
    bool    create(const std::string& caption) noexcept;
    void    destroy() noexcept;
    /**
    * Resizing with scaled values.
    * Width and height must be scaled.
    */
    void    resize(int widthPixels, int heightPixels) noexcept;
    int     getWidth() const noexcept;
    int     getHeight() const noexcept;
    int     getPixelsWidth() const noexcept;
    int     getPixelsHeight() const noexcept;
    void    swapBuffers() noexcept;
    /**
    * Get scale of this window.
    */
    float   getScale() const noexcept;
    void    readSdlMessages() noexcept;
    bool    isQuit() const noexcept;

    const Input&    getInput() const noexcept;

private:

    /**
    * Get scale of the current screen.
    */
    float   getScreenScale() const noexcept;
    bool    initializeSdl() noexcept;
    void    windowEvent(const SDL_WindowEvent& windowEvent) noexcept;

    SDL_Window* window { nullptr };
    SDL_GLContext context { nullptr };

    Input input;

    int width { 0 };
    int height { 0 };
    int pixelsWidth { 0 };
    int pixelsHeight { 0 };

    float windowScale { 1.f };

    bool sdlInitialized{ false };
    bool quit{ false };

};


}  // namespace tutorial
