#ifndef CMDPARSE_H
#define CMDPARSE_H

#include <cstring>
#include <string>
#include <list>
#include <algorithm>
#include <functional>
#include <map>
#include <iostream>

namespace osgi {

struct stringlist;
struct string : public std::string
{
    string(){}
    string(const std::string &str) : std::string(str) {}
    string(const char *str) : std::string(str ){}
    stringlist split(const char ch = ' ');
};

template<typename T>
struct list : public std::list<T>
{
    typedef std::list<T> parentType;
    bool contains(const T &v) {
        return std::find_if(parentType::begin(), parentType::end(),
                            [&](auto &val){
            return val == v;
        }) == parentType::end() ? false : true;
    }

    void push_back(const osgi::string &str)
    {
        parentType::push_back(str);
    }
};

struct stringlist : public osgi::list<osgi::string>
{
    stringlist(){}

    stringlist(int argc, char **argv) {
        for (int i = 0; i < argc; i++) {
            push_back(osgi::string(argv[i]));
        }
    }

    stringlist(const std::list<std::string> strlist) {
        std::for_each(strlist.begin(), strlist.end(),
                      [&](auto val){
            operator<<(val);
        });
    }

    stringlist &operator << (const std::string &str) {
        push_back(str);
        return *this;
    }

    stringlist &operator << (const char *str) {
        push_back(str);
        return *this;
    }

    stringlist &operator << (const osgi::stringlist &strlist) {
        for (auto val : strlist) {
            push_back(val);
        }
        return *this;
    }

    osgi::string toString() const {
        osgi::string temp;
        for (auto val : *this) {
            if (!temp.empty()) {
                temp.push_back(' ');
            }
            temp += val;
        }
        return temp;
    }

    bool contains(const std::string &str) {
        return std::find_if(begin(), end(), [&](auto val){
            if (str == val)
                return true;
            return false;
        }) == end() ? false : true;
    }

};

template<typename K, typename V>
struct map : public std::map<K, V>
{
    typedef std::map<K, V> parentType;
    std::list<K> keys(){
        K result;
        std::for_each(parentType::begin(),
                      parentType::end(),
                      [&](std::pair<K, V> val){
            result << val.first;
        });
        return result;
    }
};

std::ostream &operator <<(std::ostream &out, const stringlist &list)
{
    out << "stringlist(";
    auto itera=  list.begin();
    while (itera != list.end()) {
        out << *itera;
        itera ++;
        if (itera != list.end())
            out << ",";
    }
    out << ")";
    return out;
};

stringlist string::split(const char ch)
{
    stringlist result;
    string temp;
    for (auto &val : *this) {
        if (val == ch) {
            result.push_back(temp);
            temp.clear();
        } else {
            temp += ch;
        }
    }
    return result;
}

}

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

#endif // CMDPARSE_H
