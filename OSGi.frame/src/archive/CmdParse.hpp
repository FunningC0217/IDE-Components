#ifndef CMDPARSE_H
#define CMDPARSE_H

#include <cstring>
#include <string>
#include <list>
#include <algorithm>
#include <functional>
#include <map>
#include <iostream>

namespace std {

struct stringlist : public list<string>
{
    stringlist(){}

    stringlist(const string &str) {
        string temp;
        for (auto &ch : str) {
            if (ch == ' ') {
                this->push_back(temp);
                temp.clear();
            } else {
                temp += ch;
            }
        }
    }

    stringlist(const char **argv) {
        for (int i = 0; i < strlen((char*)argv); i++) {
            this->push_back(string(argv[i]));
        }
    }

    stringlist &operator << (const std::string &str) {
        push_back(str);
        return *this;
    }

    stringlist &operator << (const char *str) {
        push_back(str);
        return *this;
    }

    stringlist &operator << (const std::stringlist &strlist) {
        for (auto val : strlist) {
            push_back(val);
        }
        return *this;
    }

    std::string toString() const {
        std::string temp;
        for (auto val : *this) {
            if (!temp.empty()) {
                temp.push_back(' ');
            }
            temp += val;
        }
        return temp;
    }
};

int to_list(const std::string &);
}


struct CmdOption
{
    std::string option;
    std::string optionWhole;
    std::string describe;
    std::string detailed;
public:
    CmdOption(const std::string &option,
              const std::string &optionWhole,
              const std::string &describe,
              const std::string &detailed)
        : option (option)
        , optionWhole (optionWhole)
        , describe (describe)
        , detailed (detailed) {}
};

typedef std::function<void(const std::stringlist &)> CmdOptionFunc;

struct CmdParse
{
    std::map<CmdOption, CmdOptionFunc> optionMap;
    std::map<std::string, std::stringlist> optionParseArgs;
    std::stringlist args;
public:
    CmdParse(int argc, const char **argv)
        : args (doSplitArgs(std::stringlist(argv))) {
        (void)(argc);
    }

    std::stringlist doSplitArgs(const std::stringlist &args) {
        std::stringlist result;
        std::string optionKey;
        std::stringlist optionString;
        for (auto val : args) {
            auto findRes = std::find_if(optionMap.begin(), optionMap.end(),
                          [&](decltype (optionMap)::iterator itera) {
                    if (val == itera->first.option || val == itera->first.optionWhole) {return itera;}
                    return optionMap.end();
            });
            if (findRes != optionMap.end()) {
                result << optionString;
                optionParseArgs[optionKey] = optionString;
                optionKey = val;
                optionString.clear();
            } else if (!optionKey.empty()){
                optionString << val;
                break;
            }
            val = val.erase();
        }
        return result;
    }

    CmdOptionFunc operator[](const std::string &optionKey) {
        for (auto val : optionMap) {
            if (val.first.option == optionKey
                    || val.first.optionWhole == optionKey)
            {
                return val.second;
            }
        }

        return [=](const std::stringlist &optionArgs) {
            (void)(optionArgs);
            std::cout << "option: " << optionKey
                      << "No callable parameters are found. "
                         "You can execute \"-h\" or \"--help\" "
                         "to view the option list.";
            std::cout << std::endl;
        };
    }

    void call(const std::string &optionAtOne)
    {
        for (auto val : args) {
        }
    }

    void doParse() {
    }
};

#endif // CMDPARSE_H
