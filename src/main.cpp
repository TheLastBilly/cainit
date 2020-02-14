// cainit - main.cpp
//
// Copyright (c) 2019, TheLastBilly
// All rights reserved.
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <iostream>
#include <fstream>

#include "include/Parser.hpp"
#include "include/Cainit.hpp"

inline void PrintHelp()
{
    std::cout 
        << "Usage: cainit [config file]\n";
}

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        PrintHelp();
        return 1;
    }
    Parser parser;
    Cainit::ErrorValue error;
    if((error = parser.ParseFile( argv[1] )) != Cainit::ErrorValue::A_OK)
    {
        std::cout << "[ERROR]: " << Cainit::GetErrorDescription(error);
    }
    std::ofstream f;
    for( Cainit::File file : parser.files )
    {
        file.BuildSource();
        f.open( file.declarations.name);
        std::cout << "Writing to file " << file.declarations.name << ".\n";
        f << file.declarations.contents;
        f.close();

        f.open( file.definitions.name );
        std::cout << "Writing to file " << file.definitions.name << ".\n";
        f << file.definitions.contents;
        f.close();
    }
    return 0;
}
