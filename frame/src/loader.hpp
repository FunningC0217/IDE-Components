#pragma once

#include "module.hpp"

#include <functional>
#include <string>
#include <any>
#include <list>


class LibraryLoaderPrivate;
class LibraryLoader
{
    LibraryLoaderPrivate *const d;
public:
    LibraryLoader();
    virtual ~LibraryLoader();
    void setModulePaths(const std::list<std::string> &paths);
    std::list<std::string> modulePaths();
    void addModulePath(const std::string &path);
    void delModulePath(const std::string &path);
    Module_ptrs modules();
};

