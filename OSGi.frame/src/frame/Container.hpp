#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <string>
#include <map>
#include <any>
#include <vector>
#include <list>
#include <memory>
#include <algorithm>
#include <iostream>

namespace osgi {

struct stringlist;
struct string : public std::string
{
    inline string(){}
    inline string(const std::string &str) : std::string(str) {}
    inline string(const char *str) : std::string(str) {}
    stringlist split(const char ch = ' ');
};

template<typename T>
struct list : public std::list<T>
{
    typedef std::list<T> parentType;
    inline bool contains(const T &v) {
        return std::find_if(parentType::begin(), parentType::end(),
                            [&](auto &val){
            return val == v;
        }) == parentType::end() ? false : true;
    }

    inline void push_back(const osgi::string &str)
    {
        parentType::push_back(str);
    }
};

struct stringlist : public osgi::list<osgi::string>
{
    inline stringlist(){}

    inline stringlist(int argc, char **argv) {
        for (int i = 0; i < argc; i++) {
            push_back(osgi::string(argv[i]));
        }
    }

    inline stringlist(const std::list<std::string> strlist) {
        std::for_each(strlist.begin(), strlist.end(),
                      [&](auto val){
            operator<<(val);
        });
    }

    inline stringlist &operator << (const std::string &str) {
        push_back(str);
        return *this;
    }

    inline stringlist &operator << (const char *str) {
        push_back(str);
        return *this;
    }

    inline stringlist &operator << (const osgi::stringlist &strlist) {
        for (auto &val : strlist) {
            push_back(val);
        }
        return *this;
    }

    inline osgi::string toString() const {
        osgi::string temp;
        for (auto &val : *this) {
            if (!temp.empty()) {
                temp.push_back(' ');
            }
            temp += val;
        }
        return temp;
    }

    inline bool contains(const std::string &str) {
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
    inline std::list<K> keys(){
        K result;
        std::for_each(parentType::begin(),
                      parentType::end(),
                      [&](std::pair<K, V> val){
            result << val.first;
        });
        return result;
    }
};

inline std::ostream &operator <<(std::ostream &out, const stringlist &list)
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

inline stringlist string::split(const char ch)
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

#endif //CONTAINER_HPP
