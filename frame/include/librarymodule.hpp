#pragma onec

#include <string>
#include <map>
#include <any>
#include <vector>

class LibraryModule
{
    enum ImportMode
    {
        LibLoader, // from library plugin
        NetLoader  // from network plugin
    };

    // should override interface
    virtual ImportMode mode(){return LibLoader;}
    virtual std::map<std::string, std::any> property(){return {};}

    // interface from network load
    virtual std::vector<std::string> methods(){return {};}
    virtual std::any callMethod(const std::string& method, const std::vector<std::any> &){
        return {};
    }
};

typedef LibraryModule* (*Import)(const std::string &);
typedef void Export(LibraryModule *) const;

