#include "../src/module.hpp"

class Module_Bob : public Module
{
public:
    Module_Bob() = default;
};

DEF_MODULE(Module_Bob)
