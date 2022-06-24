#include "CmdParse.hpp"
#include "CppParse.hpp"

int main(int argc, char *argv[])
{
    CmdParse parse(argc, argv);

    CppParse cppParse;

    parse[{"-s", "--srouces", "", ""}] = [&](const osgi::stringlist &args)
    {
        std::cout << "-s " << args << std::endl;
        cppParse.setSources(args);
    };

    parse[{"-t", "--type", "", ""}] = [&](const osgi::stringlist &args)
    {
        std::cout << "-t " << args << std::endl;
    };

    parse[{"-r", "--root", "OSGi.Frame inclue root path", ""}]
    = [&](const osgi::stringlist &args)
    {
        if (args.size() > 0) {
            std::cout << "-r " << args.front() << std::endl;
            cppParse.setWorkdir(args.front());
        }
    };

    parse[{"-w", "--workdir", "", ""}] = [&](const osgi::stringlist &args)
    {
        if (args.size() > 0) {
            std::cout << "-w " << args.front() << std::endl;
            cppParse.setWorkdir(args.front());
        }
    };

    parse[{"-j", "-jobNumber", "", ""}] = [&](const osgi::stringlist &args){
        if (args.size() > 0) {
            std::cout << "-j " << std::stoi(args.front()) << std::endl;
            cppParse.setMaxThread(std::stoi(args.front()));
        }
    };

    parse.doParse();

    cppParse.doParse();

    return 0;
}
