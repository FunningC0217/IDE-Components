#include "loader.hpp"

#include <QLibrary>
#include <memory>
#include <filesystem>
#include <iostream>

class LibraryLoaderPrivate
{
    friend class LibraryLoader;
    std::list<std::string> modulePaths;
    Module_ptrs modules;
    static bool isModule(const std::string &path){
        std::filesystem::directory_entry entry(path);
        if (!entry.exists())
            return false;
        std::cout << "is_block_file: " << entry.is_block_file()
                  << "is_regular_file: " << entry.is_regular_file()
                  << "is_character_file: " << entry.is_character_file()
                  << "is_directory: " << entry.is_directory()
                  << "is_fifo: " << entry.is_fifo()
                  << "is_socket: " << entry.is_socket()
                  << "is_symlink: " << entry.is_symlink()
                  << "is_other:" << entry.is_other();
        return false;
    }
};

LibraryLoader::LibraryLoader()
    : d (new LibraryLoaderPrivate)
{

}

LibraryLoader::~LibraryLoader()
{
    if (d)
        delete d;
}

void LibraryLoader::setModulePaths(const std::list<std::string> &paths)
{
    d->modulePaths = paths;
}

void LibraryLoader::addModulePath(const std::string &path)
{
    d->modulePaths.push_back(path);
}

void LibraryLoader::delModulePath(const std::string &path)
{
    d->modulePaths.remove(path);
}

Module_ptrs LibraryLoader::modules()
{
    return d->modules;
}

std::list<std::string> LibraryLoader::modulePaths()
{
    return d->modulePaths;
}

