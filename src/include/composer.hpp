#pragma once

#include <iostream>

#include "cainit.hpp"
#include "parser.hpp"

class Composer
{
public:
    Composer( Parser parser );

    ~Composer();

    CainitError ComposeFile( std::string file_path );

private:
    Parser parser;
};