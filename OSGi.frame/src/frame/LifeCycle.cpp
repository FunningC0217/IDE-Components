#include "LifeCycle.hpp"

#include <memory>
#include <filesystem>
#include <iostream>
#include <algorithm>

#ifdef linux
#include <dlfcn.h>
#else __WIN32__|| __WIN64__
#endif

namespace osgi {

typedef Bundle* (*CreatFunc)();
namespace platfrom {
Bundle_ptr loadModule(const std::string &path)
{
#ifdef linux
    dlerror();
    auto handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed, " << dlerror() << "\n";
        return nullptr;
    }
    CreatFunc ptr = (CreatFunc)dlsym(handle, "OSGi.Bundle");
    if (ptr) return Bundle_ptr(ptr());
#elif __WIN32__ || __WIN64__
#endif
    return nullptr;
}
}

class LoaderPrivate
{
    friend class Loader;
    std::list<std::string> modulePaths;
    Bundle_ptrs modules;

    static bool is_shared(const std::filesystem::directory_entry &entry)
    {
        static std::list<std::string> extensions{".so", ".dll"};
        auto itera = std::find_if(extensions.begin(), extensions.end(), [=](const std::string& val)
        { return entry.path().extension() == val;});
        if (entry.is_regular_file() && itera != extensions.end()){
            return true;
        }
        return false;
    }

    static Bundle_ptr module(const std::string &path)
    {
        std::filesystem::directory_entry entry(path);
        if (!entry.exists())
            return nullptr;
        if (is_shared(entry)) {
           return platfrom::loadModule(entry.path().c_str());
        }
        return nullptr;
    }
};

Loader::Loader()
    : d (new LoaderPrivate())
{

}

Loader::~Loader()
{
    if (d)
        delete d;
}

void Loader::setModulePaths(const std::list<std::string> &paths)
{
    d->modulePaths = paths;
}

void Loader::addModulePath(const std::string &path)
{
    d->modulePaths.push_back(path);
}

void Loader::delModulePath(const std::string &path)
{
    d->modulePaths.remove(path);
}

Bundle_ptrs Loader::modules()
{
    for (auto& path : d->modulePaths) {
        for (auto& p : std::filesystem::directory_iterator(path)) {
            Bundle_ptr instance = d->module(p.path());
            if(instance) {
                instance->path = p.path();
                d->modules.push_back(std::move(instance));
            }
        }
    }
    return d->modules;
}

std::list<std::string> Loader::modulePaths()
{
    return d->modulePaths;
}


} // namespace osgi
