
#pragma once

#include <memory>

namespace tutorial
{

class IApplication
{
public:

    using Ptr = std::unique_ptr<IApplication>;

    IApplication() noexcept = default;
    virtual ~IApplication() noexcept = default;

    /**
    * Initialization before the main loop.
    */
    virtual bool    initialize(int argc, char **argv) noexcept = 0;
    /**
    * Releasing resources after the main loop.
    */
    virtual void    destroy() noexcept = 0;
    /**
    * Every frame update.
    */
    virtual void    performFrame() noexcept = 0;
    /**
    * Must returns true if app should be closed.
    */
    virtual bool    isAppQuit() noexcept = 0;

};

}  // namespace tutorial
