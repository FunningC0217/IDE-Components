#pragma onec

#include <string>
#include <map>
#include <any>
#include <vector>
#include <list>
#include <memory>

class Module
{
    enum Mode
    {
        Library, // from library plugin
        Network  // from network plugin
    };

    // should override interface
    virtual Mode mode(){return Library;}
    virtual std::string id(){return "";}
    virtual std::map<std::string, std::any> property(){return {};}

    // interface from network load
    virtual std::vector<std::string> methods(){return {};}
    virtual std::any callMethod(const std::string& method, const std::vector<std::any> &){
        return {};
    }
};

typedef std::shared_ptr<Module> Module_ptr;
typedef std::list<Module_ptr> Module_ptrs;
