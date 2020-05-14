
#pragma once

#include "iapplication.hpp"

#include <memory>

namespace tutorial
{

class ApplicationMain final
{
public:

    using Ptr = std::unique_ptr<ApplicationMain>;

    ApplicationMain(IApplication::Ptr application, int inArgc, char **inArgv) noexcept;
    virtual ~ApplicationMain() noexcept = default;

    /**
    * Execution of app.
    */
    int     execute() noexcept;

    bool    initialize() noexcept;
    void    destroy() noexcept;
    void    performFrame() noexcept;
    bool    isAppQuit() noexcept;

protected:

    void    runLoop() noexcept;

    IApplication::Ptr application_impl{ nullptr };

    int argc{ 0 };
    char **argv{ nullptr };
};

}  // namespace tutorial
