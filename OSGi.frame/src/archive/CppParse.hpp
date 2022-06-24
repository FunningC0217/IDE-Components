#ifndef CPPPARSE_HPP
#define CPPPARSE_HPP

#include "Container.hpp"

#include <mutex>

struct CppParse
{
    void doParse();
    void setSources(const osgi::stringlist &srcs);
    void setWorkdir(const osgi::string &work);
    void setFrameIncRoot(const osgi::string &root);
    void setMaxThread(int maxThread);
    osgi::stringlist getModules();
    osgi::stringlist getServices();

    osgi::string _frameIncRoot;
    osgi::string _workdir;
    osgi::stringlist _sources;
    osgi::stringlist _modules;
    osgi::stringlist _services;

    std::mutex _mutex;
    int _maxThread = 4;
    int _currThNum = 0;
};
#endif //CPPPARSE_HPP
