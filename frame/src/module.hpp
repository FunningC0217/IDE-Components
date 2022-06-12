#pragma onec

#include <string>
#include <map>
#include <any>
#include <vector>
#include <list>
#include <memory>

class Module
{
    friend class Loader;
public:
    enum Mode
    {
        Library, // from library plugin
        Network  // from network plugin
    };

    // should override interface
    inline virtual Mode mode(){return Library;}
    inline virtual std::string id(){return "";}
    inline virtual std::map<std::string, std::any> property(){return {};}

    // interface from network load
    inline virtual std::vector<std::string> methods(){return {};}
    inline virtual std::any callMethod(const std::string& method, const std::vector<std::any> &){
        return {};
    }

    inline std::string libraryPath() { return path; }
private:
    std::string path;
};

typedef std::shared_ptr<Module> Module_ptr;
typedef std::list<Module_ptr> Module_ptrs;

#define DEF_MODULE(x) \
    extern "C" x* DEF_MODULE() {return new x;}
