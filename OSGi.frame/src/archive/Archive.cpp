#pragma onec

#include "CmdParse.hpp"

int main(int argc, char *argv[])
{
    CmdParse parse(argc, argv);

    parse[{"-a","-archive", "", ""}] = [&](auto args) -> void
    {
        std::cout << args << std::endl;
    };

    parse[{"-b","-build", "", ""}] = [&](auto args) -> void
    {
        std::cout << args << std::endl;
    };

    parse.doParse();

    return 0;
}
