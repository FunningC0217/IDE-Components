#pragma onec

#include "Bundle.hpp"

#include <string>
#include <map>
#include <any>
#include <vector>
#include <list>
#include <memory>

namespace osgi {

class LoaderPrivate;
class Loader
{
    LoaderPrivate *const d;
public:
    Loader();
    virtual ~Loader();
    void setModulePaths(const std::list<std::string> &paths);
    std::list<std::string> modulePaths();
    void addModulePath(const std::string &path);
    void delModulePath(const std::string &path);
    Bundle_ptrs modules();
};

class LifeCycle
{
};

} //namespac osgi
