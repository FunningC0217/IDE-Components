#ifndef CMDPARSE_HPP
#define CMDPARSE_HPP

#include "Container.hpp"

#include <functional>

struct CmdOption
{
    osgi::string option;
    osgi::string optionWhole;
    osgi::string describe;
    osgi::string detailed;
    CmdOption(const osgi::string &option,
              const osgi::string &optionWhole,
              const osgi::string &describe,
              const osgi::string &detailed)
        : option (option)
        , optionWhole (optionWhole)
        , describe (describe)
        , detailed (detailed) {}
    bool operator < (const CmdOption &option){
        return CmdOption::option < option.option;
    }
};

bool operator < (const CmdOption &t1, const CmdOption &t2){
    return t1.option < t2.option;
}

typedef std::function<void(const osgi::stringlist &)> CmdOptionFunc;

struct CmdOptionContainer : public osgi::map<CmdOption, CmdOptionFunc>
{
    typedef osgi::map<CmdOption, CmdOptionFunc> parentType;
    bool containOption(const osgi::string &str) {
        return std::find_if(begin(), end(), [=](std::pair<CmdOption, CmdOptionFunc> val){
            if (str == val.first.option || str == val.first.optionWhole)
                return true;
            return false;
        }) == end()? false : true;
    }

    CmdOptionFunc value(const osgi::string &str) {
        auto itera = begin();
        while (itera != end()) {
            if (str == itera->first.option
                    || str == itera->first.optionWhole)
                return itera->second;
            itera ++;
        }
        return nullptr;
    }
};

struct CmdOptionArgs : public osgi::map<std::string, osgi::stringlist>
{

};

struct CmdParse
{
    CmdOptionContainer optionFuncs;
    CmdOptionArgs optionArgs;
    osgi::stringlist sourceArgs;
public:
    CmdParse(int argc, char **argv)
        : sourceArgs (osgi::stringlist(argc, argv)) {
    }

    void doSplitArgs(const osgi::stringlist &args) {
        if (args.empty())
            return;

        auto itera = args.begin();
        osgi::string optionKey;
        while (itera != args.end()) {
            if (optionFuncs.containOption(*itera)) {
                if (!optionKey.empty()) {
                    optionKey.clear();
                    continue;
                } else {
                    optionKey = *itera;
                    itera ++; continue;
                }
            }
            if (!optionKey.empty()) {
                optionArgs[optionKey] << *itera;
            } else {

            }
            itera ++;
        }
    }

    CmdOptionFunc findCallBack(const std::string &optionKey) {
        for (auto val : optionFuncs) {
            if (val.first.option == optionKey
                    || val.first.optionWhole == optionKey)
            {
                return val.second;
            }
        }

        return [=](const osgi::stringlist &optionArgs) {
            (void)(optionArgs);
            std::cout << "option: " << optionKey
                      << "No callable parameters are found. "
                         "You can execute \"-h\" or \"--help\" "
                         "to view the option list.";
            std::cout << std::endl;
        };
    }

    void doParse() {
        doSplitArgs(sourceArgs);
        for (auto val : optionArgs) {
            if (optionFuncs.containOption(val.first))
                optionFuncs.value(val.first)(val.second);
        }
    }

    CmdOptionFunc &operator[](const CmdOption &option) {
        return optionFuncs[option];
    }
};

#endif // CMDPARSE_HPP
