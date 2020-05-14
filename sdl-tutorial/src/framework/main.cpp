#include "application_main.hpp"

extern tutorial::IApplication::Ptr createApplication() noexcept;

int main(int argc, char **argv)
{
    return tutorial::ApplicationMain(createApplication(), argc, argv).execute();
}
