#include <iostream>
#include "../src/LifeCycle.hpp"
#include <optional>
#include <filesystem>

int main(int argc, char *argv[])
{
    osgi::Loader loader;
    std::filesystem::path path(argv[0]);
    loader.setModulePaths({path.parent_path()});
    auto modules = loader.modules();
    return 0;
}
