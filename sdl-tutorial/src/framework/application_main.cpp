
#include "application_main.hpp"

#ifdef EMSCRIPTEN

#include <emscripten/emscripten.h>

#endif  // EMSCRIPTEN

namespace tutorial
{

#ifdef EMSCRIPTEN

namespace
{

ApplicationMain* appEmscripten = nullptr;

void mainLoopUpdate() noexcept
{
    if (appEmscripten->isAppQuit())
    {
        emscripten_cancel_main_loop();
        return;
    }
    appEmscripten->performFrame();
}

}  // namespace

#endif  // EMSCRIPTEN

ApplicationMain::ApplicationMain(IApplication::Ptr application, int inArgc, char **inArgv) noexcept :
application_impl(std::move(application)),
argc(inArgc),
argv(inArgv)
{}

bool ApplicationMain::initialize() noexcept
{
    return application_impl->initialize(argc, argv);
}

void ApplicationMain::destroy() noexcept
{
    application_impl->destroy();
}

void ApplicationMain::performFrame() noexcept
{
    application_impl->performFrame();
}

bool ApplicationMain::isAppQuit() noexcept
{
    return application_impl->isAppQuit();
}

int ApplicationMain::execute() noexcept
{
    const auto code = initialize() ? 0 : -1;
    if (code == 0)
    {
        runLoop();
    }
    destroy();
    return code;
}

void ApplicationMain::runLoop() noexcept
{
#ifdef EMSCRIPTEN

    appEmscripten = this;
    emscripten_set_main_loop(mainLoopUpdate, 0, 1);

#else  // WIN32

    while (!isAppQuit())
    {
        performFrame();
    }

#endif  // EMSCRIPTEN
}

}  // namespace tutorial
