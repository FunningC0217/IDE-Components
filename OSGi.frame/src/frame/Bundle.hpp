#pragma onec

#include <string>
#include <filesystem>
#include <map>
#include <any>
#include <vector>
#include <list>
#include <memory>

namespace osgi {

class Bundle
{
    friend class Loader;
    friend class LifeCycle;
public:
    Bundle() = default;

    virtual void start(){}
    virtual void stop(){}

    inline std::string fileName()
    { return std::filesystem::path(path).filename(); }

    inline std::string filePath()
    { return path; }

private:
    std::string path;
};

typedef std::shared_ptr<Bundle> Bundle_ptr;
typedef std::list<Bundle_ptr> Bundle_ptrs;

} // osgi
