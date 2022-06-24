#include "CppParse.hpp"

#include <functional>
#include <iostream>
#include <thread>
#include <future>
#include <clang-c/Index.h>

std::ostream& operator<<(std::ostream& stream, const CXString& str)
{
    stream << clang_getCString(str);
    clang_disposeString(str);
    return stream;
}

typedef struct{
    CXFile file;
    CXTranslationUnit unit;
}VisitData;

CXChildVisitResult printVisitChildren(CXCursor current, CXCursor parent, CXClientData client_data)
{
    auto iData = (VisitData*)(client_data);
    CXFile visitFile;
    unsigned int line;
    unsigned int col;
    unsigned int offset;
    clang_getSpellingLocation(clang_getCursorLocation(current), &visitFile, &line, &col, &offset);

    auto srcCursor = clang_getCursor(iData->unit, clang_getCursorLocation(current));
    CXFile srcFile;
    unsigned int srcLine;
    unsigned int srcCol;
    unsigned int srcOffset;
    clang_getSpellingLocation(clang_getCursorLocation(srcCursor), &srcFile, &srcLine, &srcCol, &srcOffset);
    std::cout << "    range.begin:" << clang_getCursorExtent(srcCursor).begin_int_data << "\n"
              << "    range.end:" << clang_getCursorExtent(srcCursor).begin_int_data << "\n"
              << "    SourceCursor: " <<  clang_getCursorSpelling(srcCursor) << "\n"
              << "    Kind: " << clang_getCursorKindSpelling(clang_getCursorKind(srcCursor)) << "\n"
              << "    Type: " << clang_getTypeSpelling(clang_getCursorType(srcCursor)) << "\n"
              << "    FileName: " << clang_getFileName(srcFile) << "\n"
              << "    Line: " << srcLine << "\n"
              << "    colunm: " << srcCol << "\n"
              << "    offset: " << srcOffset << "\n"
              << "Location: \n"
              << "    Cursor: " << clang_getCursorSpelling(current) << "\n"
              << "    Kind: " << clang_getCursorKindSpelling(clang_getCursorKind(current)) << "\n"
              << "    Type: " << clang_getTypeSpelling(clang_getCursorType(current)) << "\n"
              << "    FileName: " << clang_getFileName(visitFile) << "\n"
              << "    Line: " << line << "\n"
              << "    colunm: " << col << "\n"
              << "    offset: " << offset << "\n"
              << std::endl;
    return CXChildVisit_Recurse;
};

void CppParse::doParse()
{
    auto parseFile = [=](const osgi::string &file){
        CXIndex index = clang_createIndex(0, 0);
        CXTranslationUnit unit = clang_parseTranslationUnit(
                    index,
                    file.c_str(), nullptr, 0,
                    nullptr, 0,
                    CXTranslationUnit_None);
        if (unit == nullptr) {
            std::cerr << "Unable to parse translation unit, quit thread, From : "
                      << file << std::endl;
            while (_mutex.try_lock());
            _currThNum --;
            _mutex.unlock();
            return;
        }

        VisitData data;
        data.file = clang_getFile(unit, file.c_str());
        data.unit = unit;
        clang_visitChildren(clang_getTranslationUnitCursor(unit),
                            printVisitChildren, &data);
        clang_disposeTranslationUnit(unit);
        clang_disposeIndex(index);
        while (_mutex.try_lock());
        _currThNum --;
        _mutex.unlock();
    };

    while (!_sources.empty()) {
        while (_currThNum >= _maxThread);
        osgi::string filePath;
#ifdef __linux__
        filePath = _workdir + "/" + _sources.front();
#elif __WIN32__ || __WIN64__
#endif
        _sources.pop_front();
        _currThNum ++;
        std::async(std::launch::async, parseFile, filePath);
    }
}

void CppParse::setSources(const osgi::stringlist &srcs)
{
    _sources = srcs;
}

void CppParse::setWorkdir(const osgi::string &work)
{
    _workdir = work;
}

void CppParse::setFrameIncRoot(const osgi::string &root)
{
    _frameIncRoot = root;
}

void CppParse::setMaxThread(int maxThread)
{
    _maxThread = maxThread;
}

osgi::stringlist CppParse::getModules()
{
    return _modules;
}

osgi::stringlist CppParse::getServices()
{
    return _services;
}
